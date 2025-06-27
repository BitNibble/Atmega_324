/************************************************************************
	ATMEGA 324
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date:     24/06/2025
************************************************************************/
#ifndef _ATMEGA324_H_
	#define _ATMEGA324_H_
	
/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

/*** Global Library ***/
#include "atmega324_registers.h"

/*** Global Constant & Macro ***/
#define Atmega324_GPW 0x0000
#define Atmega324_GPIOA 0x0020
#define Atmega324_GPIOB 0x0023
#define Atmega324_GPIOC 0x0026
#define Atmega324_GPIOD 0x0029
#define Atmega324GPWR_Address 0x0000
#define Atmega324AnalogComparator_Address 0x0050
#define Atmega324AnalogToDigitalConverter_Address 0x0078
#define Atmega324BootLoader_Address 0x0057
#define Atmega324CPURegister_Address 0x003E
#define Atmega324Eeprom_Address 0x003F
#define Atmega324ExternalInterrupts_Address 0x003B
#define Atmega324PORTA_Address 0x0020
#define Atmega324PORTB_Address 0x0023
#define Atmega324PORTC_Address 0x0026
#define Atmega324PORTD_Address 0x0029
#define Atmega324JtagInterface_Address 0x0051
#define Atmega324SerialPeripherialInterface_Address 0x004C
#define Atmega324TimerCounter1_Address 0x0036
#define Atmega324TimerCounter0_Address 0X0035
#define Atmega324TimerCounter2_Address 0x0037
#define Atmega324TwoWireSerialInterface_Address 0x00B8
#define Atmega324Usart0_Address 0x00C0
#define Atmega324Usart1_Address 0x00C8
#define Atmega324WatchdogTimer_Address 0x0060

/*** INSTANCE ***/
// GPWR
typedef struct {
	_uint8_t r0; // 0x0000
	_uint8_t r1; // 0x0001
	_uint8_t r2; // 0x0002
	_uint8_t r3; // 0x0003
	_uint8_t r4; // 0x0004
	_uint8_t r5; // 0x0005
	_uint8_t r6; // 0x0006
	_uint8_t r7; // 0x0007
	_uint8_t r8; // 0x0008
	_uint8_t r9; // 0x0009
	_uint8_t r10; // 0x000A
	_uint8_t r11; // 0x000B
	_uint8_t r12; // 0x000C
	_uint8_t r13; // 0x000D
	_uint8_t r14; // 0x000E
	_uint8_t r15; // 0x000F
	_uint8_t r16; // 0x0010
	_uint8_t r17; // 0x0011
	_uint8_t r18; // 0x0012
	_uint8_t r19; // 0x0013
	_uint8_t r20; // 0x0014
	_uint8_t r21; // 0x0015
	_uint8_t r22; // 0x0016
	_uint8_t r23; // 0x0017
	_uint8_t r24; // 0x0018
	_uint8_t r25; // 0x0019
	_uint16_t x; // 0x001A 0x001B
	_uint16_t y; // 0x001C 0x001D
	_uint16_t z; // 0x001E 0x001F
} _GPW_TypeDef;

// I/O Port (PORTA)
typedef struct {
	_uint8_t pin; // 0x0020
	_uint8_t ddr; // 0x0021
	_uint8_t port; // 0x0022
} _GPIOA_TypeDef;

// I/O Port (PORTB)
typedef struct {
	_uint8_t pin; // 0x0023
	_uint8_t ddr; // 0x0024
	_uint8_t port; // 0x0025
} _GPIOB_TypeDef;

// I/O Port (PORTC)
typedef struct {
	_uint8_t pin; // 0x0026
	_uint8_t ddr; // 0x0027
	_uint8_t port; // 0x0028
} _GPIOC_TypeDef;

// I/O Port (PORTD)
typedef struct {
	_uint8_t pin; // 0x0029
	_uint8_t ddr; // 0x002A
	_uint8_t port; // 0x002B
} _GPIOD_TypeDef;

// External Interrupts (EXINT)
typedef struct {
	_PCIFR_TypeDef* pcifr; // 0x003B
	uint8_t eifr; // 0x003C
	uint8_t eimsk; // 0x003D
	uint8_t fill1[ 42 ]; // ( 0x0068 - 0x003D ) - 1
	uint8_t pcicr; // 0x0068
	uint8_t eicra; // 0x0069
	uint8_t fill2; // 0x006A
	uint8_t pcmsk0; // 0x006B
	uint8_t pcmsk1; // 0x006C
	uint8_t pcmsk2; // 0x006D
	uint8_t fill3[ 5 ]; // ( 0x0073 - 0x006D ) - 1
	uint8_t pcmsk3; // 0x0073	
} Atmega324ExternalInterrupts_TypeDef;

// Analog Comparator (AC)
typedef struct {
	uint8_t acsr; // 0x0050
	uint8_t fill1[ 42 ]; // ( 0x007B - 0x0050 ) - 1
	uint8_t adcsrb; // 0x007B
	uint8_t fill2[ 3 ]; // ( 0x007F - 0x007B ) - 1
	uint8_t didr1; // 0x007F
} Atmega324AnalogComparator_TypeDef;

// Analog to Digital Converter (ADC)
typedef struct {
	_uint16_t adc; // 0x0078 0x0079
	uint8_t adcsra; // 0x007A
	uint8_t adcsrb; // 0c007B
	uint8_t admux; // 0x007C
	uint8_t didr0; // 0x007E
} Atmega324AnalogToDigitalConverter_TypeDef;

// Boot loader (BOOT_LOAD)
typedef struct {
	uint8_t spmcsr; // 0x0057
} Atmega324BootLoader_TypeDef;

// CPU Register (CPU)
typedef struct {
	uint8_t gpior0; // 0x003E
	uint8_t fill1[ 11 ]; // ( 0x004A - 0x003E ) - 1
	uint8_t gpior1; // 0x004A
	uint8_t gpior2; // 0x004B
	uint8_t smcr; // 0x0053
	uint8_t mcusr; // 0x0054
	uint8_t mcucr; // 0x0055
	uint8_t fill2[ 7 ]; // ( 0x005D - 0x0055 ) - 1
	_uint16_t sp; // 0x005D 0x005E
	uint8_t sreg; // 0x005F
	uint8_t fill3; // 0x0060
	uint8_t clkpr; // 0x0061
	uint8_t fill4[ 2 ]; // ( 0x0064 - 0x0061 ) - 1
	uint8_t prr0; // 0x0064
	uint8_t fill5; // 0x0065
	uint8_t osccal; // 0x0066
} Atmega324CPURegister_TypeDef;

// JTAG Interface (JTAG)
typedef struct {
	uint8_t ocdr; // 0x0051
	uint8_t fill[2]; // (0x0054 - 0x0051) - 1
	uint8_t mcusr; // 0x0054
	uint8_t mcucr; // 0x0055
} Atmega324JtagInterface_TypeDef;

// Serial Peripheral Interface (SPI)
typedef struct {
	uint8_t spcr0; // 0x004C
	uint8_t spsr0; // 0x004D
	uint8_t spdr0; // 0x004E
} Atmega324SerialPeripherialInterface_TypeDef;

// Two Wire Serial Interface (TWI)
typedef struct {
	uint8_t twbr; // 0x00B8
	uint8_t twsr; // 0x00B9
	uint8_t twar; // 0x00BA
	uint8_t twdr; // 0x00BB
	uint8_t twcr; // 0x00BC
	uint8_t twamr; // 0x00BD
} Atmega324TwoWireSerialInterface_TypeDef;

// USART (USART0)
typedef struct {
	uint8_t ucsr0a; // 0x00C0
	uint8_t ucsr0b; // 0x00C1
	uint8_t ucsr0c; // 0x00C2
	uint8_t fill; // 0x00C3
	_uint16_t ubrr0; // 0x00C4 0x00C5
	uint8_t udr0; // 0x00C6
} Atmega324Usart0_TypeDef;

// USART (USART1)
typedef struct {
	uint8_t ucsr1a; // 0x00C8
	uint8_t ucsr1b; // 0x00C9
	uint8_t ucsr1c; // 0x00CA
	uint8_t fill; // 0x00CB
	_uint16_t ubrr1; // 0x00CC 0x00CD
	uint8_t udr1; // 0x00CE
} Atmega324Usart1_TypeDef;

// Watchdog Timer (WDT)
typedef struct {
	uint8_t wdtcsr; // 0x0060
} Atmega324WatchdogTimer_TypeDef;

/*** Atmega 128 Procedure and Function ***/
uint16_t swapbyte(uint16_t num);
uint16_t BAUDRATEnormal(uint32_t BAUD);
uint16_t BAUDRATEdouble(uint32_t BAUD);
uint16_t BAUDRATEsynchronous(uint32_t BAUD);

/*** Procedure and Function ToolSet ***/
void set_reg(volatile uint8_t* reg, uint8_t hbits);
void clear_reg(volatile uint8_t* reg, uint8_t hbits);
uint8_t get_reg_block(uint8_t reg, uint8_t size_block, uint8_t bit_n);
void write_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);
void set_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);
uint8_t get_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);

#endif
/***EOF***/

