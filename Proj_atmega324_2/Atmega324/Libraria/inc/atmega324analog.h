/************************************************************************
Title:    Interrupt ANALOG INPUT
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Comment:
************************************************************************/
#ifndef ATMEGA324ANALOG_H
	#define ATMEGA324ANALOG_H
	
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

#if defined(__AVR_ATmega324A__)
	#include "atmega324.h"
#else
	#error "Not ATmega 324A"
#endif

#define ADC_NUMBER_SAMPLE 2 // 0 to 4.

struct ANALOG{
	// parameters
	uint8_t VREFF;
	uint8_t DIVISION_FACTOR;
	// V-table
	int (*read)(int selection);
};
typedef struct ANALOG ANALOG;

ANALOG ANALOGenable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... );

#endif
/***EOF***/
