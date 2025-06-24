/************************************************************************
	ATMEGA 324
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date:     24/06/2025
************************************************************************/
#include "atmega324_adc1.h"

static _ADC1_Module adc1_instance;

_ADC1_Module* ADC1_enable(void) {
    adc1_instance.admux  = (volatile _ADMUX_TypeDef*)  0x7C;
    adc1_instance.adcsra = (volatile _ADCSRA_TypeDef*) 0x7A;
    adc1_instance.adc    = (volatile _uint16_t*)       0x78;
    adc1_instance.adcsrb = (volatile _ADCSRB_TypeDef*) 0x7B;
    adc1_instance.didr1  = (volatile _uint8_t*)        0x7F;

    return &adc1_instance;
}
