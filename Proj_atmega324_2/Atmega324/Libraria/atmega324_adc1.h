/************************************************************************
	ATMEGA 324
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date:     24/06/2025
************************************************************************/
#ifndef ATMEGA324_ADC1_H
	#define ATMEGA324_ADC1_H

#include "atmega324_registers.h"

/*** ADC1 Module Struct ***/
typedef struct {
	_ADMUX_TypeDef* admux;     // 0x79
	_ADCSRA_TypeDef* adcsra;   // 0x7A
	_uint16_t* adc;             // 0x78 (ADCL:ADCH)
	_ADCSRB_TypeDef* adcsrb;   // 0x7B
	_uint8_t* didr1;            // 0x7C
} _ADC1_Module;

/*** Accessor ***/
_ADC1_Module* ADC1_enable(void);

#endif // ATMEGA324_ADC1_H
