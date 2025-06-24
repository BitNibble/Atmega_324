#include "adc0.h"

// Memory-mapped register base addresses for ADC0 on ATmega324
#define _ADC_ADCL_ADDR   ((volatile uint8_t*)0x0078)
#define _ADC_ADCH_ADDR   ((volatile uint8_t*)0x0079)
#define _ADC_ADCSRA_ADDR ((volatile _ADCSRA_TypeDef*)0x007A)
#define _ADC_ADCSRB_ADDR ((volatile _ADCSRB_TypeDef*)0x007B)
#define _ADC_ADMUX_ADDR  ((volatile _ADMUX_TypeDef*)0x007C)
#define _ADC_DIDR0_ADDR  ((volatile _DIDR0_TypeDef*)0x007E)
#define _ADC_DIDR1_ADDR  ((volatile _DIDR1_TypeDef*)0x007F)

// Internal instance
static _ADC0_Module _adc0_instance;

// Singleton accessor
const _ADC0_Module* ADC0(void) {
    return &_adc0_instance;
}

// Initialization function
const _ADC0_Module* ADC0_enable(void) {
    // Bind ADCL and ADCH together via shared structure
    _adc0_instance.adc_data = (volatile _ADCData_TypeDef*)_ADC_ADCL_ADDR;

    // Bind all individual registers
    _adc0_instance.adcsra = _ADC_ADCSRA_ADDR;
    _adc0_instance.adcsrb = _ADC_ADCSRB_ADDR;
    _adc0_instance.admux  = _ADC_ADMUX_ADDR;
    _adc0_instance.didr0  = _ADC_DIDR0_ADDR;
    _adc0_instance.didr1  = _ADC_DIDR1_ADDR;

    return &_adc0_instance;
}
