#ifndef ATMEGA324_ADC0_H
#define ATMEGA324_ADC0_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*** REGISTER TYPES ***/

// ADC Data (ADCL + ADCH)
typedef volatile union {
	struct {
		uint8_t l; // ADCL (0x0078)
		uint8_t h; // ADCH (0x0079)
	} par;
	uint16_t var;
} _ADCData_TypeDef;

// ADCSRA – ADC Control and Status Register A (0x007A)
typedef volatile union {
	struct {
		uint8_t adps0 : 1;
		uint8_t adps1 : 1;
		uint8_t adps2 : 1;
		uint8_t adie  : 1;
		uint8_t adif  : 1;
		uint8_t adate : 1;
		uint8_t adsc  : 1;
		uint8_t aden  : 1;
	} par;
	uint8_t var;
} _ADCSRA_TypeDef;

// ADCSRB – ADC Control and Status Register B (0x007B)
typedef volatile union {
	struct {
		uint8_t adts0 : 1;
		uint8_t adts1 : 1;
		uint8_t adts2 : 1;
		uint8_t mux5  : 1;
		uint8_t       : 4;
	} par;
	uint8_t var;
} _ADCSRB_TypeDef;

// ADMUX – ADC Multiplexer Selection Register (0x007C)
typedef volatile union {
	struct {
		uint8_t mux0  : 1;
		uint8_t mux1  : 1;
		uint8_t mux2  : 1;
		uint8_t mux3  : 1;
		uint8_t mux4  : 1;
		uint8_t adlar : 1;
		uint8_t refs0 : 1;
		uint8_t refs1 : 1;
	} par;
	uint8_t var;
} _ADMUX_TypeDef;

// DIDR0 – Digital Input Disable Register 0 (0x007E)
typedef volatile union {
	struct {
		uint8_t adc0d : 1;
		uint8_t adc1d : 1;
		uint8_t adc2d : 1;
		uint8_t adc3d : 1;
		uint8_t adc4d : 1;
		uint8_t adc5d : 1;
		uint8_t adc6d : 1;
		uint8_t adc7d : 1;
	} par;
	uint8_t var;
} _DIDR0_TypeDef;

// DIDR1 – Digital Input Disable Register 1 (0x007F)
typedef volatile union {
	struct {
		uint8_t ain0d : 1;
		uint8_t ain1d : 1;
		uint8_t       : 6;
	} par;
	uint8_t var;
} _DIDR1_TypeDef;

/*** MODULE TYPE ***/

typedef struct _ADC0_Module {
	_ADCData_TypeDef*  adc_data; // 0x0078 (ADCL + ADCH)
	_ADCSRA_TypeDef*   adcsra;   // 0x007A
	_ADCSRB_TypeDef*   adcsrb;   // 0x007B
	_ADMUX_TypeDef*    admux;    // 0x007C
	_DIDR0_TypeDef*    didr0;    // 0x007E
	_DIDR1_TypeDef*    didr1;    // 0x007F
} _ADC0_Module;

/*** INTERFACE ***/

// Call once to initialize internal pointers
const _ADC0_Module* ADC0_enable(void);

// Access the singleton instance after initialization
const _ADC0_Module* ADC0(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_ADC0_H
