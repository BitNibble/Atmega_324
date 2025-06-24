#include "twi.h"

static _TWI_Module iface;

_TWI_Module* TWI_enable(void) {
	iface.twbr  = (_TWBR_TypeDef*)  0x50;
	iface.twsr  = (_TWSR_TypeDef*)  0x51;
	iface.twar  = (_TWAR_TypeDef*)  0x52;
	iface.twdr  = (_TWDR_TypeDef*)  0x53;
	iface.twcr  = (_TWCR_TypeDef*)  0x56;
	iface.twamr = (_TWAMR_TypeDef*) 0x54;

	return &iface;
}
