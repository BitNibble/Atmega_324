#include "pinchange.h"

static _PinChange_Module iface;

_PinChange_Module* PinChange_enable(void) {
	iface.PCIFR = (_PCIFR_TypeDef*) 0x003B;   // Pin Change Interrupt Flag Register
	iface.PCICR = (_PCICR_TypeDef*) 0x006B;   // Pin Change Interrupt Control Register
	iface.PCMSK0 = (_PCMSK0_TypeDef*) 0x006C; // Pin Change Mask Register 0
	iface.PCMSK1 = (_PCMSK1_TypeDef*) 0x006D; // Pin Change Mask Register 1
	iface.PCMSK2 = (_PCMSK2_TypeDef*) 0x0078; // Pin Change Mask Register 2
	iface.PCMSK3 = (_PCMSK3_TypeDef*) 0x0079; // Pin Change Mask Register 3

	return &iface;
}
