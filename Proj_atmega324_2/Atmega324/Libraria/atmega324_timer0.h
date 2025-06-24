#ifndef TIMER0_H
#define TIMER0_H

#include <stdint.h>

/*** Timer0 Register Typedefs ***/
typedef volatile union {
	struct {
		uint8_t tov0 : 1;
		uint8_t ocf0a : 1;
		uint8_t ocf0b : 1;
		uint8_t : 5;
	} par;
	uint8_t var;
} _TIFR0_TypeDef;

typedef volatile union {
	struct {
		uint8_t tocie0b : 1;
		uint8_t tocie0a : 1;
		uint8_t toie0 : 1;
		uint8_t : 5;
	} par;
	uint8_t var;
} _TIMSK0_TypeDef;

typedef volatile union {
	struct {
		uint8_t com0a1 : 1;
		uint8_t com0a0 : 1;
		uint8_t com0b1 : 1;
		uint8_t com0b0 : 1;
		uint8_t wgm01 : 1;
		uint8_t wgm00 : 1;
		uint8_t : 2;
	} par;
	uint8_t var;
} _TCCR0A_TypeDef;

typedef volatile union {
	struct {
		uint8_t cs00 : 1;
		uint8_t cs01 : 1;
		uint8_t cs02 : 1;
		uint8_t wgm02 : 1;
		uint8_t : 2;
		uint8_t foc0b : 1;
		uint8_t foc0a : 1;
	} par;
	uint8_t var;
} _TCCR0B_TypeDef;

typedef volatile union {
	struct {
		uint8_t b0 : 1; 
		uint8_t b1 : 1; 
		uint8_t b2 : 1; 
		uint8_t b3 : 1;
		uint8_t b4 : 1; 
		uint8_t b5 : 1; 
		uint8_t b6 : 1; 
		uint8_t b7 : 1;
	} par;
	uint8_t var;
} _TCNT0_TypeDef;

typedef volatile union {
	struct {
		uint8_t b0 : 1; 
		uint8_t b1 : 1; 
		uint8_t b2 : 1; 
		uint8_t b3 : 1;
		uint8_t b4 : 1; 
		uint8_t b5 : 1; 
		uint8_t b6 : 1; 
		uint8_t b7 : 1;
	} par;
	uint8_t var;
} _OCR0A_TypeDef;

typedef volatile union {
	struct {
		uint8_t b0 : 1; 
		uint8_t b1 : 1; 
		uint8_t b2 : 1; 
		uint8_t b3 : 1;
		uint8_t b4 : 1; 
		uint8_t b5 : 1; 
		uint8_t b6 : 1; 
		uint8_t b7 : 1;
	} par;
	uint8_t var;
} _OCR0B_TypeDef;

/*** Timer0 Module Struct ***/
typedef struct {
	_TIFR0_TypeDef* tifr0;
	_TIMSK0_TypeDef* timsk0;
	_TCCR0A_TypeDef* tccr0a;
	_TCCR0B_TypeDef* tccr0b;
	_TCNT0_TypeDef*  tcnt0;
	_OCR0A_TypeDef*  ocr0a;
	_OCR0B_TypeDef*  ocr0b;
} _TIMER0_Module;

/*** Initialization function ***/
_TMER0_Module* TIMER0_enable(void);

#endif /* TIMER0_H */
