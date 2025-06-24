#ifndef ATMEGA324_PINCHANGE_H
#define ATMEGA324_PINCHANGE_H

#include <stdint.h>

/*** Pin Change Interrupt Flag Register ***/
typedef volatile union {
	struct {
		uint8_t pcif0:1;
		uint8_t pcif1:1;
		uint8_t pcif2:1;
		uint8_t pcif3:1;
		uint8_t :4;
	} par;
	uint8_t var;
} _PCIFR_TypeDef;

/*** Pin Change Interrupt Control Register ***/
typedef volatile union {
	struct {
		uint8_t pcie0:1;
		uint8_t pcie1:1;
		uint8_t pcie2:1;
		uint8_t pcie3:1;
		uint8_t :4;
	} par;
	uint8_t var;
} _PCICR_TypeDef;

/*** Pin Change Mask Register 0 ***/
typedef volatile union {
	struct {
		uint8_t pcint0:1;
		uint8_t pcint1:1;
		uint8_t pcint2:1;
		uint8_t pcint3:1;
		uint8_t pcint4:1;
		uint8_t pcint5:1;
		uint8_t pcint6:1;
		uint8_t pcint7:1;
	} par;
	uint8_t var;
} _PCMSK0_TypeDef;

/*** Pin Change Mask Register 1 ***/
typedef volatile union {
	struct {
		uint8_t pcint8:1;
		uint8_t pcint9:1;
		uint8_t pcint10:1;
		uint8_t pcint11:1;
		uint8_t pcint12:1;
		uint8_t pcint13:1;
		uint8_t pcint14:1;
		uint8_t pcint15:1;
	} par;
	uint8_t var;
} _PCMSK1_TypeDef;

/*** Pin Change Mask Register 2 ***/
typedef volatile union {
	struct {
		uint8_t pcint16:1;
		uint8_t pcint17:1;
		uint8_t pcint18:1;
		uint8_t pcint19:1;
		uint8_t pcint20:1;
		uint8_t pcint21:1;
		uint8_t pcint22:1;
		uint8_t pcint23:1;
	} par;
	uint8_t var;
} _PCMSK2_TypeDef;

/*** Pin Change Mask Register 3 ***/
typedef volatile union {
	struct {
		uint8_t pcint24:1;
		uint8_t pcint25:1;
		uint8_t pcint26:1;
		uint8_t pcint27:1;
		uint8_t pcint28:1;
		uint8_t pcint29:1;
		uint8_t pcint30:1;
		uint8_t pcint31:1;
	} par;
	uint8_t var;
} _PCMSK3_TypeDef;

/*** Module struct ***/
typedef struct {
	_PCIFR_TypeDef* PCIFR;
	_PCICR_TypeDef* PCICR;
	_PCMSK0_TypeDef* PCMSK0;
	_PCMSK1_TypeDef* PCMSK1;
	_PCMSK2_TypeDef* PCMSK2;
	_PCMSK3_TypeDef* PCMSK3;
} _PinChange_Module;

#ifdef __cplusplus
extern "C" {
#endif

_PPinChange_Module* PinChange_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_PINCHANGE_H
