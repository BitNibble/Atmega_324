#ifndef ATMEGA324_TIMER3_H
#define ATMEGA324_TIMER3_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

typedef volatile union {
	struct { _uint8_t l, h; } par;
	uint16_t var;
} _uint16_t;

/*** Timer3 Registers ***/
typedef volatile union {
	struct { uint8_t tov3:1, ocf3a:1, ocf3b:1, :2, icf3:1, :2; } par;
	uint8_t var;
} _TIFR3_TypeDef; // 0x0038

typedef volatile union {
	struct { uint8_t toie3:1, ocie3a:1, ocie3b:1, :2, icie3:1, :2; } par;
	uint8_t var;
} _TIMSK3_TypeDef; // 0x0071

typedef volatile union {
	struct {
		uint8_t wgm30:1, wgm31:1,
		res0:2,
		com3b0:1, com3b1:1, com3a0:1, com3a1:1;
	} par;
	uint8_t var;
} _TCCR3A_TypeDef; // 0x0090

typedef volatile union {
	struct {
		uint8_t cs30:1, cs31:1, cs32:1,
		wgm32:1, wgm33:1, :1,
		ices3:1, icnc3:1;
	} par;
	uint8_t var;
} _TCCR3B_TypeDef; // 0x0091

typedef volatile union {
	struct { uint8_t foc3b:1, foc3a:1, :6; } par;
	uint8_t var;
} _TCCR3C_TypeDef; // 0x0092

typedef _uint16_t _TCNT3_TypeDef;  // 0x0094
typedef _uint16_t _OCR3A_TypeDef;  // 0x0098
typedef _uint16_t _OCR3B_TypeDef;  // 0x009A
typedef _uint16_t _ICR3_TypeDef;   // 0x0096

/*** Timer3 Module Interface ***/
typedef struct {
	_TIFR3_TypeDef*  tifr3;
	_TIMSK3_TypeDef* timsk3;
	_TCCR3A_TypeDef* tccr3a;
	_TCCR3B_TypeDef* tccr3b;
	_TCCR3C_TypeDef* tccr3c;
	_TCNT3_TypeDef*  tcnt3;
	_OCR3A_TypeDef*  ocr3a;
	_OCR3B_TypeDef*  ocr3b;
	_ICR3_TypeDef*   icr3;
} _TIMER3_Module;

#ifdef __cplusplus
extern "C" {
#endif

_TIMER3_Module* TIMER3_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_TIMER3_H
