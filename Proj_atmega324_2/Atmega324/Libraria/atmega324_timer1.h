#ifndef TIMER1_H
#define TIMER1_H

#include <stdint.h>

/*** Timer1 Register Typedefs ***/

typedef volatile union {
	struct {
		uint8_t tov1  : 1;
		uint8_t ocf1a : 1;
		uint8_t ocf1b : 1;
		uint8_t       : 2;
		uint8_t icf1  : 1;
		uint8_t       : 2;
	} par;
	uint8_t var;
} _TIFR1_TypeDef;

typedef volatile union {
	struct {
		uint8_t toie1  : 1;
		uint8_t ocie1a : 1;
		uint8_t ocie1b : 1;
		uint8_t        : 2;
		uint8_t icie1  : 1;
		uint8_t        : 2;
	} par;
	uint8_t var;
} _TIMSK1_TypeDef;

typedef volatile union {
	struct {
		uint8_t wgm10  : 1;
		uint8_t wgm11  : 1;
		uint8_t        : 2;
		uint8_t com1b0 : 1;
		uint8_t com1b1 : 1;
		uint8_t com1a0 : 1;
		uint8_t com1a1 : 1;
	} par;
	uint8_t var;
} _TCCR1A_TypeDef;

typedef volatile union {
	struct {
		uint8_t cs10  : 1;
		uint8_t cs11  : 1;
		uint8_t cs12  : 1;
		uint8_t wgm12 : 1;
		uint8_t wgm13 : 1;
		uint8_t       : 1;
		uint8_t ices1 : 1;
		uint8_t icnc1 : 1;
	} par;
	uint8_t var;
} _TCCR1B_TypeDef;

typedef volatile union {
	struct {
		uint8_t foc1b : 1;
		uint8_t foc1a : 1;
		uint8_t       : 6;
	} par;
	uint8_t var;
} _TCCR1C_TypeDef;

typedef volatile union {
	struct {
		uint8_t l;
		uint8_t h;
	} par;
	uint16_t var;
} _TCNT1_TypeDef;

typedef volatile union {
	struct {
		uint8_t l;
		uint8_t h;
	} par;
	uint16_t var;
} _OCR1A_TypeDef;

typedef volatile union {
	struct {
		uint8_t l;
		uint8_t h;
	} par;
	uint16_t var;
} _OCR1B_TypeDef;

typedef volatile union {
	struct {
		uint8_t l;
		uint8_t h;
	} par;
	uint16_t var;
} _ICR1_TypeDef;

/*** Timer1 Module Struct ***/
typedef struct {
	_TIFR1_TypeDef*  tifr1;
	_TIMSK1_TypeDef* timsk1;
	_TCCR1A_TypeDef* tccr1a;
	_TCCR1B_TypeDef* tccr1b;
	_TCCR1C_TypeDef* tccr1c;
	_TCNT1_TypeDef*  tcnt1;
	_OCR1A_TypeDef*  ocr1a;
	_OCR1B_TypeDef*  ocr1b;
	_ICR1_TypeDef*   icr1;
} _TIMER1_Module;

/*** Initialization Function ***/
_TIMER1_Module* TIMER1_enable(void);

#endif /* TIMER1_H */
