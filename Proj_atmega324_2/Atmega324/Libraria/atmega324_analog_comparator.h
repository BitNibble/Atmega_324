#ifndef ATMEGA324_ANALOG_COMPARATOR_H
#define ATMEGA324_ANALOG_COMPARATOR_H

#include <stdint.h>

/*** Analog Comparator Control and Status Register (ACSR) ***/
typedef volatile union {
	struct {
		uint8_t acif:1;    // Analog Comparator Interrupt Flag
		uint8_t acie:1;    // Analog Comparator Interrupt Enable
		uint8_t acic:1;    // Analog Comparator Input Capture Enable
		uint8_t acisc:1;   // Analog Comparator Sense Control bit 0
		uint8_t acis1:1;   // Analog Comparator Sense Control bit 1
		uint8_t acd:1;     // Analog Comparator Disable
		uint8_t :2;        // Reserved
	} par;
	uint8_t var;
} _ACSR_TypeDef;

/*** ADC Control and Status Register B (for ACME bit) ***/
typedef volatile union {
	struct {
		uint8_t :5;
		uint8_t acme:1;    // Analog Comparator Multiplexer Enable
		uint8_t :2;
	} par;
	uint8_t var;
} _ADCSRB_TypeDef;

/*** Digital Input Disable Register 1 (DIDR1) ***/
typedef volatile union {
	struct {
		uint8_t adc0d:1;   // ADC0 Digital Input Disable
		uint8_t adc1d:1;   // ADC1 Digital Input Disable
		uint8_t ac0d:1;    // Analog Comparator Input Disable (AIN0)
		uint8_t ac1d:1;    // Analog Comparator Input Disable (AIN1)
		uint8_t :4;
	} par;
	uint8_t var;
} _DIDR1_TypeDef;

/*** Module struct ***/
typedef struct {
	_ACSR_TypeDef* ACSR;
	_ADCSRB_TypeDef* ADCSRB;
	_DIDR1_TypeDef* DIDR1;
} _AnalogComparator_Module;

#ifdef __cplusplus
extern "C" {
#endif

_AnalogComparator_Module* AnalogComparator_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_ANALOG_COMPARATOR_H
