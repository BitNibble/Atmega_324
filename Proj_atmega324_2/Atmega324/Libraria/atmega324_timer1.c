#include "timer1.h"

static _TIMER1_Module iface;

_TIMER1_Module* TIMER1_enable(void) {
	iface.tifr1   = (_TIFR1_TypeDef*)  0x36;
	iface.timsk1  = (_TIMSK1_TypeDef*) 0x6F;
	iface.tccr1a  = (_TCCR1A_TypeDef*) 0x80;
	iface.tccr1b  = (_TCCR1B_TypeDef*) 0x81;
	iface.tccr1c  = (_TCCR1C_TypeDef*) 0x82;
	iface.tcnt1   = (_TCNT1_TypeDef*)  0x84;
	iface.ocr1a   = (_OCR1A_TypeDef*)  0x88;
	iface.ocr1b   = (_OCR1B_TypeDef*)  0x8A;
	iface.icr1    = (_ICR1_TypeDef*)   0x86;

	return &iface;
}
