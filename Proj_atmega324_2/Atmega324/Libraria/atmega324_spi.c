#include "spi.h"

static _SPI_Module iface;

_SPI_Module* SPI_enable(void) {
	iface.spcr = (_SPCR_TypeDef*) 0x4C;
	iface.spsr = (_SPSR_TypeDef*) 0x4D;
	iface.spdr = (_SPDR_TypeDef*) 0x4E;

	return &iface;
}
