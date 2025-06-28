/*************************************************************************
	ATMEGA 324 USART1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ATmega324
Update:   26/06/2025
Comment:
	Stable
*************************************************************************/
/*** File Library ***/
#include "atmega324_usart1.h"
#include "buffer.h"
#include <avr/interrupt.h>
#include <string.h>

/*** File Variable ***/
static USART1 atmega324_usart1;

static BUFF rx1buff;
static UARTvar UART1_Rx;
static UARTvar UART1_RxBuf[UART1_RX_BUFFER_SIZE] = {0};
static const uint16_t uart1_rx_buffer_size = UART1_RX_BUFFER_SIZE - 1;
static uint8_t UART1_LastRxError;
static uint8_t uart1flag;

/*** File Header ***/
UARTvar uart1_read(void);
UARTvar uart1_getch(void);
UARTvar* uart1_gets(void);
void uart1_rxflush(void);
void uart1_write(UARTvar data);
void uart1_putch(UARTvar c);
void uart1_puts(UARTvar* s);
/*** Complimentary functions ***/
uint8_t USART1ReceiveComplete(void);
uint8_t USART1TransmitComplete(void);
uint8_t USART1DataRegisterEmpty(void);
uint8_t USART1FrameError(void);
uint8_t USART1DataOverRun(void);
uint8_t USART1ParityError(void);
uint8_t USART1ReadErrors(void);
void USART1ClearErrors(void);
void USART1DoubleTransmissionSpeed(void);

/*** Procedure & Function ***/
USART1 usart1_enable( uint32_t baud, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity )
{
	// ATMEGA128enable();
	uart1flag = 1;
	uint16_t ubrr = 0;
	rx1buff = buff_enable( uart1_rx_buffer_size, UART1_RxBuf );
	ubrr = BAUDRATEnormal(baud);
	// registers
	atmega324_usart1.reg = usart1_instance();
	// V-table
	atmega324_usart1.read = uart1_read;
	atmega324_usart1.getch = uart1_getch;
	atmega324_usart1.gets = uart1_gets;
	atmega324_usart1.rxflush = uart1_rxflush;
	atmega324_usart1.write = uart1_write;
	atmega324_usart1.putch = uart1_putch;
	atmega324_usart1.puts = uart1_puts;
	// Set baud rate
	if ( ubrr & 0x8000 ) {
		USART1DoubleTransmissionSpeed(); // Enable 2x speed
		ubrr = BAUDRATEdouble(baud);
	}
	atmega324_usart1.reg->ubrr1->var = ubrr;
	// Enable USART receiver and transmitter and receive complete interrupt
	atmega324_usart1.reg->ucsr1b->var = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
	
	#ifdef URSEL1 // Set frame format: asynchronous, 8 data, no parity, 1 stop bit
		atmega324_usart1.reg->ucsr1c->var = (1 << UMSEL1) | (3 << UCSZ10);
	#else
		switch(FDbits){
			case 9:
				atmega324_usart1.reg->ucsr1b->var |= (1 << UCSZ12);
				atmega324_usart1.reg->ucsr1c->var |= (3 << UCSZ10);
			break;
			case 8:
				atmega324_usart1.reg->ucsr1b->var &= ~(1 << UCSZ12);
				atmega324_usart1.reg->ucsr1c->var |= (3 << UCSZ10);
			break;
			case 7:
				atmega324_usart1.reg->ucsr1b->var &= ~(1 << UCSZ12);
				atmega324_usart1.reg->ucsr1c->var |= (1 << UCSZ11);
				atmega324_usart1.reg->ucsr1c->var &= ~(1 << UCSZ10);
			break;
			case 6:
				atmega324_usart1.reg->ucsr1b->var &= ~(1 << UCSZ12);
				atmega324_usart1.reg->ucsr1c->var &= ~(1 << UCSZ11);
				atmega324_usart1.reg->ucsr1c->var |= (1 << UCSZ10);
			break;
			case 5:
				atmega324_usart1.reg->ucsr1b->var &= ~(1 << UCSZ12);
				atmega324_usart1.reg->ucsr1c->var &= ~(3 << UCSZ10);
			break;
			default:
				atmega324_usart1.reg->ucsr1b->var &= ~(1 << UCSZ12);
				atmega324_usart1.reg->ucsr1c->var |= (3 << UCSZ10);
			break;
		}
		switch(Stopbits){
			case 1:
				atmega324_usart1.reg->ucsr1c->var &= ~(1 << USBS1);
			break;
			case 2:
				atmega324_usart1.reg->ucsr1c->var |= (1 << USBS1);
			break;
			default:
				atmega324_usart1.reg->ucsr1c->var &= ~(1 << USBS1);
			break;
		}
		switch(Parity){
			case 0: // NONE
				atmega324_usart1.reg->ucsr1c->var &= ~(3 << UPM10);
			break;
			case 2: // EVEN
				atmega324_usart1.reg->ucsr1c->var |= (1 << UPM11);
				atmega324_usart1.reg->ucsr1c->var &= ~(1 << UPM10);
			break;
			case 3: // ODD
				atmega324_usart1.reg->ucsr1c->var |= (3 << UPM10);
			break;
			default:
				atmega324_usart1.reg->ucsr1c->var &= ~(3 << UPM10);
			break;
		}
	#endif
	cpu_instance()->sreg->par.i = 1;
	
	return atmega324_usart1;
}

USART1* usart1(void){ return &atmega324_usart1; }

UARTvar uart1_read(void)
{
	UARTvar c;
	c = UART1_Rx;
	UART1_Rx = 0;
	return c;
}
UARTvar uart1_getch(void)
{
	return uart1_read();
}
UARTvar* uart1_gets(void)
{
	return rx1buff.raw(&rx1buff.par);
}
void uart1_rxflush(void)
{
	rx1buff.flush(&rx1buff.par);
	UART1_LastRxError = 0;
}
void uart1_write(UARTvar data)
{
	uint16_t timeout;
	atmega324_usart1.reg->ucsr1b->var |= 1 << UDRIE1;
	atmega324_usart1.reg->udr1->var = data;
	for( timeout = 600; !USART1DataRegisterEmpty() && timeout; timeout-- ); // minimum -> +/- 450
	//for( ; !USART1DataRegisterEmpty(); ); // without timeout
}
void uart1_putch(UARTvar c)
{
	uart1_write(c);
}
void uart1_puts(UARTvar* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		uart1_putch(tmp);
	}
}

/*** Interrupts ***/
SIGNAL(UART1_RECEIVE_INTERRUPT)
{
	unsigned char bit9;
	unsigned char usr;
	
	usr  = USART1ReadErrors();
	bit9 = atmega324_usart1.reg->ucsr1b->var;
	bit9 = 0x01 & (bit9 >> 1);
 	   
	if(usr){ UART1_LastRxError = usr; }
	
	UART1_Rx = atmega324_usart1.reg->udr1->var;
	rx1buff.push(&rx1buff.par, UART1_Rx);
}

SIGNAL(UART1_TRANSMIT_INTERRUPT)
{
	atmega324_usart1.reg->ucsr1b->var &= ~(1 << UDRIE1);
}

/*** Complimentary functions ***/
char* usart1_messageprint(USART1* uart, char* oneshot, char* msg, const char* endl)
{
	char* ptr;
	uint8_t length;
	uint8_t endlength = strlen(endl);
	if(uart1flag){ *oneshot = 0; uart1flag = 0; uart->rxflush();} // the matrix
	ptr = uart->gets();
	length = strlen(ptr);
	if(length >= endlength){
		if( !strcmp( ptr+(length-endlength), endl ) ){
			strcpy(oneshot, ptr); strcpy(msg, ptr); uart1flag = 0xFF;
		}
		// default
		//else if( !strcmp( ptr+(length-endlength), "\r" ) ){ strcpy(oneshot, ptr); strcpy(msg, ptr); uart1flag = 0xFF; }
		//else if( !strcmp( ptr+(length-endlength), "\n" ) ){ strcpy(oneshot, ptr); strcpy(msg, ptr); uart1flag = 0xFF; }
	}
	return ptr;
}

/*** Auxiliar ***/
uint8_t USART1ReceiveComplete(void)
{
	return (UCSR1A & (1 << RXC1));
}
uint8_t USART1TransmitComplete(void)
{
	return (UCSR1A & (1 << TXC1));
}
uint8_t USART1DataRegisterEmpty(void)
{
	return (UCSR1A & (1 << UDRE1));
}
uint8_t USART1FrameError(void)
{
	return (UCSR1A & (1 << FE1));
}
uint8_t USART1DataOverRun(void)
{
	return (UCSR1A & (1 << DOR1));
}
uint8_t USART1ParityError(void)
{
	return (UCSR1A & (1 << FE1));
}
uint8_t USART1ReadErrors(void)
{
	return get_reg_block(UCSR1A,3,2);
}
void USART1ClearErrors(void)
{
	set_reg_block(&UCSR1A,3,2,0);
}
void USART1DoubleTransmissionSpeed(void)
{
	set_reg_block(&UCSR1A,4,1,1);
}

/***EOF***/

