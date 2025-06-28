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
	Atmega324TimerCounter0_TypeDef* reg;
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
	Atmega324TimerCounter1_TypeDef* reg;
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
	Atmega324TimerCounter2_TypeDef* reg;
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

