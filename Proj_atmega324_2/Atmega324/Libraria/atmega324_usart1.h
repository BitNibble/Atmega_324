/************************************************************************
	ATMEGA 324 USART1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ATmega324
Update:   26/06/2025
Comment:

************************************************************************/
#ifndef _ATMEGA324_USART1_H_
	#define _ATMEGA324_USART1_H_

/*** Global Library ***/
#include "atmega324.h"

/*** Global Constant & Macro ***/
#ifndef GLOBAL_INTERRUPT_ENABLE
	#define GLOBAL_INTERRUPT_ENABLE 7
#endif
#ifndef UART1_RX_BUFFER_SIZE
	#define UART1_RX_BUFFER_SIZE 32
#endif

#define UARTvar char

// Parity choices
#define NONE 0
#define EVEN 2
#define ODD 3

#if ( ( UART1_RX_BUFFER_SIZE ) >= ( RAMEND - 0x60 ) )
	#error "size of UART_RX_BUFFER_SIZE + UART_TX_BUFFER_SIZE larger than size of SRAM"
#endif

#if defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega644P__) 
	// ATmega with two USART
	
	#define UART_FRAME_ERROR		0x0800              /* Framing Error by UART        */
	#define UART_OVERRUN_ERROR		0x0400              /* Overrun condition by UART    */
	#define UART_BUFFER_OVERFLOW	0x0200              /* receive ring buffer overflow */
	#define UART_NO_DATA			0x0100              /* no receive data available    */
	#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
	#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
#else
	#error "Not Atmega 324"
#endif

/*** Global Variable ***/
typedef struct {
	// registers
	_UCSR1A_TypeDef* ucsr1a;
	_UCSR1B_TypeDef* ucsr1b;
	_UCSR1C_TypeDef* ucsr1c;
	_uint16_t* ubrr1;
	_uint8_t* udr1;
	// prototype pointers
	UARTvar (*read)(void);
	UARTvar (*getch)(void);
	UARTvar* (*gets)(void);
	void (*rxflush)(void);
	void (*write)(UARTvar data);
	void (*putch)(UARTvar c);
	void (*puts)(UARTvar* s);
}USART1;

/*** Global ***/
USART1* usart1(void);
USART1 usart1_enable( uint32_t baud, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity );

char* usart1_messageprint(USART1* uart, char* oneshot, char* msg, const char* endl);

#endif

/***EOF***/

