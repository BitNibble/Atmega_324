#include "analog_comparator.h"

static _AnalogComparator_Module iface;

_AnalogComparator_Module* AnalogComparator_enable(void) {
	iface.ACSR = (_ACSR_TypeDef*) 0x0058;    // ACSR Register
	iface.ADCSRB = (_ADCSRB_TypeDef*) 0x0071; // ADCSRB Register (ACME bit)
	iface.DIDR1 = (_DIDR1_TypeDef*) 0x0075;  // DIDR1 Register

	return &iface;
}
