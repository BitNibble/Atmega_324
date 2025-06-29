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

// Analog Comparator (AC)
typedef struct {
	_ACSR_TypeDef* acsr; // 0x0050
	_ADCSRB_TypeDef* adcsrb; // 0x007B
	_DIDR1_TypeDef* didr1; // 0x007F
} Atmega324AnalogComparator_TypeDef;

Atmega324AnalogComparator_TypeDef* ac_reg(void);

// Analog to Digital Converter (ADC)
typedef struct {
	_uint16_t* adc; // 0x0078 0x0079
	_ADCSRA_TypeDef* adcsra; // 0x007A
	_ADCSRB_TypeDef* adcsrb; // 0c007B
	_ADMUX_TypeDef* admux; // 0x007C
	_DIDR0_TypeDef* didr0; // 0x007E
} Atmega324AnalogToDigitalConverter_TypeDef;

Atmega324AnalogToDigitalConverter_TypeDef* adc_reg(void);

// Boot loader (BOOT_LOAD)
typedef struct {
	_SPMCSR_TypeDef* spmcsr; // 0x0057
} Atmega324BootLoader_TypeDef;

Atmega324BootLoader_TypeDef* boot_reg(void);

// CPU Register (CPU)
typedef struct {
	_uint8_t* gpior0; // 0x003E
	_uint8_t* gpior1; // 0x004A
	_uint8_t* gpior2; // 0x004B
	_SMCR_TypeDef* smcr; // 0x0053
	_MCUSR_TypeDef* mcusr; // 0x0054
	_MCUCR_TypeDef* mcucr; // 0x0055
	_uint16_t* sp; // 0x005D 0x005E
	_SREG_TypeDef* sreg; // 0x005F
	_CLKPR_TypeDef* clkpr; // 0x0061
	_PRR_TypeDef* prr0; // 0x0064
	_uint8_t* osccal; // 0x0066
} Atmega324CPURegister_TypeDef;

Atmega324CPURegister_TypeDef* cpu_reg(void);

// EEPROM (EEPROM)
typedef struct {
	_EECR_TypeDef* eecr; // 0x003F
	_uint8_t* eedr; // 0x0040
	_uint16_t* eear; // 0x0041 0x0042
} Atmega324Eeprom_TypeDef;

Atmega324Eeprom_TypeDef* eeprom_reg(void);

// External Interrupts (EXINT)
typedef struct {
	_PCIFR_TypeDef* pcifr; // 0x003B
	_EIFR_TypeDef* eifr; // 0x003C
	_EIMSK_TypeDef* eimsk; // 0x003D
	_PCICR_TypeDef* pcicr; // 0x0068
	_EICRA_TypeDef* eicra; // 0x0069
	_PCMSK0_TypeDef* pcmsk0; // 0x006B
	_PCMSK1_TypeDef* pcmsk1; // 0x006C
	_PCMSK2_TypeDef* pcmsk2; // 0x006D
	_PCMSK3_TypeDef* pcmsk3; // 0x0073
} Atmega324ExternalInterrupts_TypeDef;

Atmega324ExternalInterrupts_TypeDef* exint_reg(void);

// I/O Port (PORTA)
typedef struct {
	_uint8_t* pin; // 0x0020
	_uint8_t* ddr; // 0x0021
	_uint8_t* port; // 0x0022
} _GPIOA_TypeDef;

_GPIOA_TypeDef* gpioa_reg(void);

// I/O Port (PORTB)
typedef struct {
	_uint8_t* pin; // 0x0023
	_uint8_t* ddr; // 0x0024
	_uint8_t* port; // 0x0025
} _GPIOB_TypeDef;

_GPIOB_TypeDef* gpiob_reg(void);

// I/O Port (PORTC)
typedef struct {
	_uint8_t* pin; // 0x0026
	_uint8_t* ddr; // 0x0027
	_uint8_t* port; // 0x0028
} _GPIOC_TypeDef;

_GPIOC_TypeDef* gpioc_reg(void);

// I/O Port (PORTD)
typedef struct {
	_uint8_t* pin; // 0x0029
	_uint8_t* ddr; // 0x002A
	_uint8_t* port; // 0x002B
} _GPIOD_TypeDef;

_GPIOD_TypeDef* gpiod_reg(void);

// JTAG Interface (JTAG)
typedef struct {
	_uint8_t* ocdr; // 0x0051
	_MCUSR_TypeDef* mcusr; // 0x0054
	_MCUCR_TypeDef* mcucr; // 0x0055
} Atmega324JtagInterface_TypeDef;

Atmega324JtagInterface_TypeDef* jtag_reg(void);

// Serial Peripheral Interface (SPI)
typedef struct {
	_SPCR_TypeDef* spcr0; // 0x004C
	_SPSR_TypeDef* spsr0; // 0x004D
	_uint8_t* spdr0; // 0x004E
} Atmega324SerialPeripherialInterface_TypeDef;

Atmega324SerialPeripherialInterface_TypeDef* spi_reg(void);

// Timer/Counter, 16-bit (TC1)
typedef struct {
	_TIFR1_Typedef* tifr1; // 0x0036
	_TIMSK1_TypeDef* timsk1; // 0x006F
	_TCCR1A_TypeDef* tccr1a; // 0x0080
	_TCCR1B_TypeDef* tccr1b; // 0x0081
	_TCCR1C_TypeDef* tccr1c; // 0x0082
	_uint16_t* tcnt1; // 0x0084 0x0085
	_uint16_t* icr1; // 0x0086 0x0087
	_uint16_t* ocr1a; // 0x0088 0x0089
	_uint16_t* ocr1b; // 0x008A 0x008B
} Atmega324TimerCounter1_TypeDef;

Atmega324TimerCounter1_TypeDef* tc1_reg(void);

// Timer/Counter, 8-bit (TC0)
typedef struct {
	_TIFR0_Typedef* tifr0; // 0x0035
	_GTCCR_TypeDef* gtccr; // 0x0043
	_TCCR0A_TypeDef* tccr0a; // 0x0044
	_TCCR0B_TypeDef* tccr0b; // 0x0045
	_uint8_t* tcnt0; // 0x0046
	_uint8_t* ocr0a; // 0x0047
	_uint8_t* ocr0b; // 0x0048
	_TIMSK0_TypeDef* timsk0; // 0x006E	
} Atmega324TimerCounter0_TypeDef;

Atmega324TimerCounter0_TypeDef* tc0_reg(void);

// Timer/Counter, 8-bit Async (TC2)
typedef struct {
	_TIFR2_Typedef* tifr2; // 0x0037
	_GTCCR_TypeDef* gtccr; // 0x0043
	_TIMSK2_TypeDef* timsk2; // 0x0070
	_TCCR2A_TypeDef* tccr2a; // 0x00B0
	_TCCR2B_TypeDef* tccr2b; // 0x00B1
	_uint8_t* tcnt2; // 0x00B2
	_uint8_t* ocr2a; // 0x00B3
	_uint8_t* ocr2b; // 0x00B4
	_ASSR_TypeDef* assr; // 0x00B6
} Atmega324TimerCounter2_TypeDef;

Atmega324TimerCounter2_TypeDef* tc2_reg(void);

// Two Wire Serial Interface (TWI)
typedef struct {
	_uint8_t* twbr; // 0x00B8
	_TWSR_TypeDef* twsr; // 0x00B9
	_TWAR_TypeDef* twar; // 0x00BA
	_uint8_t* twdr; // 0x00BB
	_TWCR_TypeDef* twcr; // 0x00BC
	_TWAMR_TypeDef* twamr; // 0x00BD
} Atmega324TwoWireSerialInterface_TypeDef;

Atmega324TwoWireSerialInterface_TypeDef* twi_reg(void);

// USART (USART0)
typedef struct {
	_UCSR0A_TypeDef* ucsr0a; // 0x00C0
	_UCSR0B_TypeDef* ucsr0b; // 0x00C1
	_UCSR0C_TypeDef* ucsr0c; // 0x00C2
	_uint16_t* ubrr0; // 0x00C4–0x00C5 (UBRR0H: 0x00C4, UBRR0L: 0x00C5)
	_uint8_t* udr0; // 0x00C6
} Atmega324Usart0_TypeDef;

Atmega324Usart0_TypeDef* usart0_reg(void);

// USART (USART1)
typedef struct {
	_UCSR1A_TypeDef* ucsr1a; // 0x00C8
	_UCSR1B_TypeDef* ucsr1b; // 0x00C9
	_UCSR1C_TypeDef* ucsr1c; // 0x00CA
	_uint16_t* ubrr1; // 0x00CC–0x00CD (UBRR1H: 0x00CC, UBRR1L: 0x00CD)
	_uint8_t* udr1; // 0x00CE
} Atmega324Usart1_TypeDef;

Atmega324Usart1_TypeDef* usart1_reg(void);

// Watchdog Timer (WDT)
typedef struct {
	_WDTCSR_TypeDef* wdtcsr; // 0x0060
} Atmega324WatchdogTimer_TypeDef;

Atmega324WatchdogTimer_TypeDef* wdt_reg(void);

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

