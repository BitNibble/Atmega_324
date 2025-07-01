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
#if defined(__AVR_ATmega324A__)
	#include "atmega324.h"
#else
	#error "Not ATmega 324A"
#endif

/*** Global Constant & Macro ***/
#ifndef UART1_RX_BUFFER_SIZE
	#define UART1_RX_BUFFER_SIZE 32
#endif

#define UARTvar char

// Parity choices
#define NONE 0
#define EVEN 2
#define ODD 3
#ifndef SRAMEND
	#define SRAMSTART 0x0100
	#define SRAMEND 0x08FF
#endif

#if ( ( UART1_RX_BUFFER_SIZE ) >= ( SRAMEND ) - SRAMSTART )
	#error "size of UART1_RX_BUFFER_SIZE larger than size of SRAM"
#endif

#if defined(__AVR_ATmega324A__)
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

