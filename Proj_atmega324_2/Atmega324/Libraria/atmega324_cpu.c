#include "cpu.h"

static _CPU_Module iface;

_CPU_Module* CPU_enable(void) {
	iface.SREG   = (_SREG_TypeDef*) 0x5F;
	iface.MCUCR  = (_MCUCR_TypeDef*) 0x55;
	iface.MCUCSR = (_MCUCSR_TypeDef*) 0x54;
	iface.SMCR   = (_SMCR_TypeDef*) 0x53;

	return &iface;
}
