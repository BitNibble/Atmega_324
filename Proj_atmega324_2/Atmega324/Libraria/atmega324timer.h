/*************************************************************************
	ATMEGA 324 TIMER HANDLERS 
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 324 at 8Mhz
*************************************************************************/
#ifndef ATMEGA324TIMER_H_
  #define ATMEGA324TIMER_H_
  
#include "atmega324.h"

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

typedef struct {
	// registers
	_SREG_TypeDef* sreg; // 0x005F
	_TIFR0_Typedef* tifr0; // 0x0035
	_GTCCR_TypeDef* gtccr; // 0x0043
	_TCCR0A_TypeDef* tccr0a; // 0x0044
	_TCCR0B_TypeDef* tccr0b; // 0x0045
	_uint8_t* tcnt0; // 0x0046
	_uint8_t* ocr0a; // 0x0047
	_uint8_t* ocr0b; // 0x0048
	_TIMSK0_TypeDef* timsk0; // 0x006E
	// prototype pointers
	void (*compoutmodeA)(uint8_t compoutmode);
	void (*compoutmodeB)(uint8_t compoutmode);
	void (*compareA)(uint8_t compare);
	void (*compareB)(uint8_t compare);
	void (*start)(uint16_t prescaler);
	void (*stop)(void);
} TIMER_COUNTER0;
/**/
typedef struct {
	// registers
	_SREG_TypeDef* sreg; // 0x005F
	_TIFR1_Typedef* tifr1; // 0x0036
	_TIMSK1_TypeDef* timsk1; // 0x006F
	_TCCR1A_TypeDef* tccr1a; // 0x0080
	_TCCR1B_TypeDef* tccr1b; // 0x0081
	_TCCR1C_TypeDef* tccr1c; // 0x0082
	_uint16_t* tcnt1; // 0x0084 0x0085
	_uint16_t* icr1; // 0x0086 0x0087
	_uint16_t* ocr1a; // 0x0088 0x0089
	_uint16_t* ocr1b; // 0x008A 0x008B
	// prototype pointers
	void (*compoutmodeA)(uint8_t compoutmode);
	void (*compoutmodeB)(uint8_t compoutmode);
	void (*compareA)(uint16_t compare);
	void (*compareB)(uint16_t compare);
	void (*start)(uint16_t prescaler);
	void (*stop)(void);
} TIMER_COUNTER1;
/**/
typedef struct {
	// registers
	_SREG_TypeDef* sreg; // 0x005F
	_TIFR2_Typedef* tifr2; // 0x0037
	_GTCCR_TypeDef* gtccr; // 0x0043
	_TIMSK2_TypeDef* timsk2; // 0x0070
	_TCCR2A_TypeDef* tccr2a; // 0x00B0
	_TCCR2B_TypeDef* tccr2b; // 0x00B1
	_uint8_t* tcnt2; // 0x00B2
	_uint8_t* ocr2a; // 0x00B3
	_uint8_t* ocr2b; // 0x00B4
	_ASSR_TypeDef* assr; // 0x00B6
	// prototype pointers
	void (*compoutmodeA)(uint8_t compoutmode);
	void (*compoutmodeB)(uint8_t compoutmode);
	void (*compareA)(uint8_t compare);
	void (*compareB)(uint8_t compare);
	void (*start)(uint16_t prescaler);
	void (*stop)(void);
} TIMER_COUNTER2;

TIMER_COUNTER0 TIMER_COUNTER0enable(uint8_t wavegenmode, uint8_t interrupt);
TIMER_COUNTER0* TC0(void);
TIMER_COUNTER1 TIMER_COUNTER1enable(uint8_t wavegenmode, uint8_t interrupt);
TIMER_COUNTER1* TC1(void);
TIMER_COUNTER2 TIMER_COUNTER2enable(uint8_t wavegenmode, uint8_t interrupt);
TIMER_COUNTER2* TC2(void);
#endif
/***EOF***/

