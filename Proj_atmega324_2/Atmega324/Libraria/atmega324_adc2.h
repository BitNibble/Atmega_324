#ifndef ATMEGA324_ADC2_H
#define ATMEGA324_ADC2_H

#include <stdint.h>

/*** Common Types ***/
typedef volatile union {
	struct {
		uint8_t b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
	} par;
	uint8_t var;
} _uint8_t;

typedef volatile union {
	struct {
		_uint8_t l, h;
	} par;
	uint16_t var;
} _uint16_t;

/*** ADC2 Register Typedefs ***/
typedef volatile union {
	struct {
		uint8_t mux0:1, mux1:1, mux2:1, mux3:1, mux4:1, adlar:1, refs0:1, refs1:1;
	} par;
	uint8_t var;
} _ADMUX2_TypeDef;

typedef volatile union {
	struct {
		uint8_t aden:1, adsc:1, adate:1, adif:1, adie:1, adps0:1, adps1:1, adps2:1;
	} par;
	uint8_t var;
} _ADCSRA2_TypeDef;

typedef volatile union {
	struct {
		uint8_t adts0:1, adts1:1, adts2:1, :5;
	} par;
	uint8_t var;
} _ADCSRB2_TypeDef;

/*** ADC2 Module Struct ***/
typedef struct {
	_ADMUX2_TypeDef* admux;     // 0x7D
	_ADCSRA2_TypeDef* adcsra;   // 0x7E
	_uint16_t* adc;             // 0x7C (ADCL:ADCH)
	_ADCSRB2_TypeDef* adcsrb;   // 0x7F
	_uint8_t* didr2;            // 0x80
} _ADC2_Module;

/*** Accessor ***/
_ADC2_Module* ADC2_enable(void);

#endif // ATMEGA324_ADC2_H
