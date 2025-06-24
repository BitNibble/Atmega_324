#include "wdt.h"

static _WDT_Module iface;

_WDT_Module* WDT_enable(void) {
	iface.WDTCR = (_WDTCR_TypeDef*) 0x60; // WDTCSR register address on ATmega324

	return &iface;
}
