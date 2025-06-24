#include "adc2.h"

// Static instance
static _ADC2_Module adc2_instance;

_ADC2_Module* ADC2_enable(void) {
	adc2_instance.admux  = (_ADMUX2_TypeDef*) 0x007D;
	adc2_instance.adcsra = (_ADCSRA2_TypeDef*) 0x007E;
	adc2_instance.adc    = (_uint16_t*) 0x007C; // ADCL:ADCH
	adc2_instance.adcsrb = (_ADCSRB2_TypeDef*) 0x007F;
	adc2_instance.didr2  = (_uint8_t*) 0x0080;
	return &adc2_instance;
}
