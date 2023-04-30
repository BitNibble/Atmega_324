/*********************************************************
	ATMEGA 324 MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date: 30042023
Comment: 
	Virtual Image Atmega 324 mapping.
**********************************************************/
#ifndef _ATMEGA324MAPPING_H_
	#define _ATMEGA324MAPPING_H_

/*** Global Library ***/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <inttypes.h>
// Comment out modules not being used
// RAW IMAGE
#include "atmega324.h"
// MODULES
#include "atmega324analog.h"
#include "atmegaeeprom.h"
#include "atmega324timer.h"

/*** Global Variable ***/
// SECOND LAYER
// GPWR
typedef struct {
	Atmega324GPWR_TypeDef* reg;
}Atmega324GPWR;

// Analog Comparator (AC)
typedef struct {
	Atmega324AnalogComparator_TypeDef* reg;
}Atmega324AnalogComparator;

// Analog to Digital Converter (ADC)
typedef struct {
	Atmega324AnalogToDigitalConverter_TypeDef* reg;
	#if defined(_ATMEGA324ANALOG_H_)
		ANALOG (*enable)( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... );
	#endif
} Atmega324AnalogToDigitalConverter;

// Boot loader (BOOT_LOAD)
typedef struct {
	Atmega324BootLoader_TypeDef* reg;
} Atmega324BootLoader;

// CPU Register (CPU)
typedef struct {
	Atmega324CPURegister_TypeDef* reg;
} Atmega324CPURegister;

// EEPROM (EEPROM)
typedef struct {
	Atmega324Eeprom_TypeDef* reg;
	#if defined(_ATMEGAEEPROM_H_)
		EEPROM (*enable)(void);
	#endif
} Atmega324Eeprom;

// External Interrupts (EXINT)
typedef struct {
	Atmega324ExternalInterrupts_TypeDef* reg;
	#if defined(_ATMEGA324INTERRUPT_H_)
		INTERRUPT (*enable)(void);
	#endif
} Atmega324ExternalInterrupts;

// I/O Port (PORTA)
typedef struct {
	Atmega324PORTA_TypeDef* reg;
}Atmega324PORTA;

// I/O Port (PORTB)
typedef struct {
	Atmega324PORTB_TypeDef* reg;
}Atmega324PORTB;

// I/O Port (PORTC)
typedef struct {
	Atmega324PORTC_TypeDef* reg;
}Atmega324PORTC;

// I/O Port (PORTD)
typedef struct {
	Atmega324PORTD_TypeDef* reg;
}Atmega324PORTD;

// JTAG Interface (JTAG)
typedef struct {
	Atmega324JtagInterface_TypeDef* reg;
} Atmega324JtagInterface;

// Serial Peripheral Interface (SPI)
typedef struct {
	Atmega324SerialPeripherialInterface_TypeDef* reg;
	#if defined(_ATMEGA324SPI_H_)
		SPI (*enable)(uint8_t master_slave_select, uint8_t data_order,  uint8_t data_modes, uint8_t prescaler);
	#endif
} Atmega324SerialPeripherialInterface;

// Timer/Counter, 16-bit (TC1)
typedef struct {
	Atmega324TimerCounter1_TypeDef* reg;
	#if defined(_ATMEGA324TIMER_H_)
		TIMER_COUNTER1 (*enable)(unsigned char wavegenmode, unsigned char interrupt);
	#endif
} Atmega324TimerCounter1;

// Timer/Counter, 8-bit (TC0)
typedef struct {
	Atmega324TimerCounter0_TypeDef* reg;
	#if defined(_ATMEGA324TIMER_H_)
		TIMER_COUNTER0 (*enable)(unsigned char wavegenmode, unsigned char interrupt);
	#endif
} Atmega324TimerCounter0;

// Timer/Counter, 8-bit Async (TC2)
typedef struct {
	Atmega324TimerCounter2_TypeDef* reg;
	#if defined(_ATMEGA324TIMER_H_)
		TIMER_COUNTER2 (*enable)(unsigned char wavegenmode, unsigned char interrupt);
	#endif
} Atmega324TimerCounter2;

// Two Wire Serial Interface (TWI)
typedef struct {
	Atmega324TwoWireSerialInterface_TypeDef* reg;
	#if defined(_ATMEGA324TWI_H_)
		TWI (*enable)(uint8_t atmega_ID,  uint8_t prescaler);
	#endif
} Atmega324TwoWireSerialInterface;

// USART (USART0)
typedef struct {
	Atmega324Usart0_TypeDef* reg;
	#if defined(_ATMEGA324UART_H_)
		UART0 (*enable)(unsigned int baudrate, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity );
	#endif
} Atmega324Usart0;

// USART (USART1)
typedef struct {
	Atmega324Usart1_TypeDef* reg;
	#if defined(_ATMEGA324UART_H_)
		UART1 (*enable)(unsigned int baudrate, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity );
	#endif
} Atmega324Usart1;

// Watchdog Timer (WDT)
typedef struct {
	Atmega324WatchdogTimer_TypeDef* reg;
} Atmega324WatchdogTimer;

// ATMEGA 324 IMAGE
typedef struct {
	Atmega324GPWR gpwr;
	Atmega324AnalogComparator ac;
	Atmega324AnalogToDigitalConverter adc;
	Atmega324BootLoader boot_load;
	Atmega324CPURegister cpu;
	Atmega324Eeprom eeprom;
	Atmega324ExternalInterrupts exint;
	Atmega324PORTA porta;
	Atmega324PORTB portb;
	Atmega324PORTC portc;
	Atmega324PORTD portd;
	Atmega324JtagInterface jtag;
	Atmega324SerialPeripherialInterface spi;
	Atmega324TimerCounter1 tc1;
	Atmega324TimerCounter0 tc0;
	Atmega324TimerCounter2 tc2;
	Atmega324TwoWireSerialInterface twi;
	Atmega324Usart0 usart0;
	Atmega324Usart1 usart1;
	Atmega324WatchdogTimer wdt;
	
	HighLowByte HLbyte;
	uint16_t (*readhlbyte)(HighLowByte reg);
	uint16_t (*readlhbyte)(HighLowByte reg);
	HighLowByte (*writehlbyte)(uint16_t val);
	HighLowByte (*writelhbyte)(uint16_t val);
	uint16_t (*swapbyte)(uint16_t num);
	/**************************************/
}ATMEGA324;

/*** Global Header ***/
ATMEGA324 ATMEGA324enable(void);

#endif
/***EOF***/

