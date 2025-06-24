#include "eeprom.h"

static _EEPROM_Module iface;

_EEPROM_Module* EEPROM_enable(void) {
	iface.eecr  = (_EECR_TypeDef*)  0x3C;
	iface.eedr  = (_EEDR_TypeDef*)  0x3D;
	iface.eearl = (_EEARL_TypeDef*) 0x3E;
	iface.eearh = (_EEARH_TypeDef*) 0x3F;
	return &iface;
}
