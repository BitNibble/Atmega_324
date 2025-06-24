#ifndef ATMEGA324_TIMER2_H
#define ATMEGA324_TIMER2_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

/*** Timer2 Registers ***/
typedef volatile union {
	struct { uint8_t tov2:1, ocf2a:1, ocf2b:1, :5; } par;
	uint8_t var;
} _TIFR2_TypeDef; // 0x0037

typedef volatile union {
	struct { uint8_t toie2:1, ocie2a:1, ocie2b:1, :5; } par;
	uint8_t var;
} _TIMSK2_TypeDef; // 0x0070

typedef volatile union {
	struct {
		uint8_t wgm20:1, wgm21:1, :2,
		com2b0:1, com2b1:1, com2a0:1, com2a1:1;
	} par;
	uint8_t var;
} _TCCR2A_TypeDef; // 0x00B0

typedef volatile union {
	struct {
		uint8_t cs20:1, cs21:1, cs22:1,
		wgm22:1, :2, foc2b:1, foc2a:1;
	} par;
	uint8_t var;
} _TCCR2B_TypeDef; // 0x00B1

typedef _uint8_t _TCNT2_TypeDef;  // 0x00B2
typedef _uint8_t _OCR2A_TypeDef;  // 0x00B3
typedef _uint8_t _OCR2B_TypeDef;  // 0x00B4

typedef volatile union {
	struct {
		uint8_t tcr2ub:1, ocr2aub:1, ocr2bub:1,
		tcn2ub:1, as2:1, exclk:1, :2;
	} par;
	uint8_t var;
} _ASSR_TypeDef; // 0x00B6

/*** Timer2 Module Interface ***/
typedef struct {
	_TIFR2_TypeDef*  tifr2;
	_TIMSK2_TypeDef* timsk2;
	_TCCR2A_TypeDef* tccr2a;
	_TCCR2B_TypeDef* tccr2b;
	_TCNT2_TypeDef*  tcnt2;
	_OCR2A_TypeDef*  ocr2a;
	_OCR2B_TypeDef*  ocr2b;
	_ASSR_TypeDef*   assr;
} _TIMER2_Module;

#ifdef __cplusplus
extern "C" {
#endif

_TIMER2_Module* TIMER2_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_TIMER2_H
