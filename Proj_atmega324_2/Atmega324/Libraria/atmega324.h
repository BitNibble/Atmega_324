/************************************************************************
	ATMEGA 324 REGISTERS
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date: 29/04/2023
Comment:
	Virtual Image Atmega 324.
************************************************************************/
#ifndef _ATMEGA324_H_
	#define _ATMEGA324_H_
	
/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
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

/*** Global Variable ***/
// Low Byte High Byte
typedef struct {
	uint8_t L; // Lower Address
	uint8_t H; // Higher Address
} HighLowByte;

/*** MAIN HARDWARE LAYER ***/
// GPWR
typedef struct {
	uint8_t r0; // 0x0000
	uint8_t r1; // 0x0001
	uint8_t r2; // 0x0002
	uint8_t r3; // 0x0003
	uint8_t r4; // 0x0004
	uint8_t r5; // 0x0005
	uint8_t r6; // 0x0006
	uint8_t r7; // 0x0007
	uint8_t r8; // 0x0008
	uint8_t r9; // 0x0009
	uint8_t r10; // 0x000A
	uint8_t r11; // 0x000B
	uint8_t r12; // 0x000C
	uint8_t r13; // 0x000D
	uint8_t r14; // 0x000E
	uint8_t r15; // 0x000F
	uint8_t r16; // 0x0010
	uint8_t r17; // 0x0011
	uint8_t r18; // 0x0012
	uint8_t r19; // 0x0013
	uint8_t r20; // 0x0014
	uint8_t r21; // 0x0015
	uint8_t r22; // 0x0016
	uint8_t r23; // 0x0017
	uint8_t r24; // 0x0018
	uint8_t r25; // 0x0019
	uint8_t xl; // 0x001A
	uint8_t xh; // 0x001B
	uint8_t yl; // 0x001C
	uint8_t yh; // 0x001D
	uint8_t zl; // 0x001E
	uint8_t zh; // 0x001F
} Atmega324GPWR_TypeDef;

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
	HighLowByte adc; // 0x0078 0x0079
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
	HighLowByte sp; // 0x005D 0x005E
	uint8_t sreg; // 0x005F
	uint8_t fill3; // 0x0060
	uint8_t clkpr; // 0x0061
	uint8_t fill4[ 2 ]; // ( 0x0064 - 0x0061 ) - 1
	uint8_t prr0; // 0x0064
	uint8_t fill5; // 0x0065
	uint8_t osccal; // 0x0066
} Atmega324CPURegister_TypeDef;

// EEPROM (EEPROM)
typedef struct {
	uint8_t eecr; // 0x003F
	uint8_t eedr; // 0x0040
	HighLowByte eear; // 0x0041 0x0042
} Atmega324Eeprom_TypeDef;

// External Interrupts (EXINT)
typedef struct {
	uint8_t pcifr; // 0x003B
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

// I/O Port (PORTA)
typedef struct {
	uint8_t pin; // 0x0020
	uint8_t ddr; // 0x0021
	uint8_t port; // 0x0022
} Atmega324PORTA_TypeDef;

// I/O Port (PORTB)
typedef struct {
	uint8_t pin; // 0x0023
	uint8_t ddr; // 0x0024
	uint8_t port; // 0x0025
} Atmega324PORTB_TypeDef;

// I/O Port (PORTC)
typedef struct {
	uint8_t pin; // 0x0026
	uint8_t ddr; // 0x0027
	uint8_t port; // 0x0028
} Atmega324PORTC_TypeDef;

// I/O Port (PORTD)
typedef struct {
	uint8_t pin; // 0x0029
	uint8_t ddr; // 0x002A
	uint8_t port; // 0x002B
} Atmega324PORTD_TypeDef;

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

// Timer/Counter, 16-bit (TC1)
typedef struct {
	uint8_t tifr1; // 0x0036
	uint8_t fill1[ 56 ]; // ( 0x006F - 0x0036 ) - 1
	uint8_t timsk1; // 0x006F
	uint8_t fill2[ 16 ]; // ( 0x0080 - 0x006F ) - 1
	uint8_t tccr1a; // 0x0080
	uint8_t tccr1b; // 0x0081
	uint8_t tccr1c; // 0x0082
	uint8_t fill3; // 0x0083
	HighLowByte tcnt1; // 0x0084 0x0085
	HighLowByte icr1; // 0x0086 0x0087
	HighLowByte ocr1a; // 0x0088 0x0089
	HighLowByte ocr1b; // 0x008A 0x008B
} Atmega324TimerCounter1_TypeDef;

// Timer/Counter, 8-bit (TC0)
typedef struct {
	uint8_t tifr0; // 0x0035
	uint8_t fill1[ 13 ]; // ( 0x0043 - 0x0035 ) - 1
	uint8_t gtccr; // 0x0043
	uint8_t tccr0a; // 0x0044
	uint8_t tccr0b; // 0x0045
	uint8_t tcnt0; // 0x0046
	uint8_t ocr0a; // 0x0047
	uint8_t ocr0b; // 0x0048
	uint8_t fill2[ 37 ]; // ( 0x006E - 0x0048 ) - 1
	uint8_t timsk0; // 0x006E	
} Atmega324TimerCounter0_TypeDef;

// Timer/Counter, 8-bit Async (TC2)
typedef struct {
	uint8_t tifr2; // 0x0037
	uint8_t fill1[ 11 ]; // ( 0x0043 - 0x0037 ) - 1
	uint8_t gtccr; // 0x0043
	uint8_t fill2[ 44 ]; // ( 0x0070 - 0x0043 ) - 1
	uint8_t timsk2; // 0x0070
	uint8_t fill3[ 63 ]; // ( 0x00B0 - 0x0070 ) - 1
	uint8_t tccr2a; // 0x00B0
	uint8_t tccr2b; // 0x00B1
	uint8_t tcnt2; // 0x00B2
	uint8_t ocr2a; // 0x00B3
	uint8_t ocr2b; // 0x00B4
	uint8_t fill4; // 0x00B5
	uint8_t assr; // 0x00B6
} Atmega324TimerCounter2_TypeDef;

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
	HighLowByte ubrr0; // 0x00C4 0x00C5
	uint8_t udr0; // 0x00C6
} Atmega324Usart0_TypeDef;

// USART (USART1)
typedef struct {
	uint8_t ucsr1a; // 0x00C8
	uint8_t ucsr1b; // 0x00C9
	uint8_t ucsr1c; // 0x00CA
	uint8_t fill; // 0x00CB
	HighLowByte ubrr1; // 0x00CC 0x00CD
	uint8_t udr1; // 0x00CE
} Atmega324Usart1_TypeDef;

// Watchdog Timer (WDT)
typedef struct {
	uint8_t wdtcsr; // 0x0060
} Atmega324WatchdogTimer_TypeDef;

#endif
/***EOF***/

