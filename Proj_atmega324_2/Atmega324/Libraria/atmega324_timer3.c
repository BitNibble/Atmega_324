#include "timer3.h"

static _TIMER3_Module iface;

_TIMER3_Module* TIMER3_enable(void) {
	iface.tifr3   = (_TIFR3_TypeDef*)  0x38;
	iface.timsk3  = (_TIMSK3_TypeDef*) 0x71;
	iface.tccr3a  = (_TCCR3A_TypeDef*) 0x90;
	iface.tccr3b  = (_TCCR3B_TypeDef*) 0x91;
	iface.tccr3c  = (_TCCR3C_TypeDef*) 0x92;
	iface.tcnt3   = (_TCNT3_TypeDef*)  0x94;
	iface.icr3    = (_ICR3_TypeDef*)   0x96;
	iface.ocr3a   = (_OCR3A_TypeDef*)  0x98;
	iface.ocr3b   = (_OCR3B_TypeDef*)  0x9A;

	return &iface;
}
