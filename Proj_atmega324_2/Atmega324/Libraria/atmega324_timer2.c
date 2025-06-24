#include "timer2.h"

static _TIMER2_Module iface;

_TIMER2_Module* TIMER2_enable(void) {
	iface.tifr2   = (_TIFR2_TypeDef*)  0x37;
	iface.timsk2  = (_TIMSK2_TypeDef*) 0x70;
	iface.tccr2a  = (_TCCR2A_TypeDef*) 0xB0;
	iface.tccr2b  = (_TCCR2B_TypeDef*) 0xB1;
	iface.tcnt2   = (_TCNT2_TypeDef*)  0xB2;
	iface.ocr2a   = (_OCR2A_TypeDef*)  0xB3;
	iface.ocr2b   = (_OCR2B_TypeDef*)  0xB4;
	iface.assr    = (_ASSR_TypeDef*)   0xB6;

	return &iface;
}
