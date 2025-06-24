#include "port.h"

static _PORT_Module iface;

_PORT_Module* PORT_enable(void) {
	iface.PORTA = (_PORTx_TypeDef*) 0x22;
	iface.DDRA  = (_DDR_TypeDef*)   0x21;
	iface.PINA  = (_PINx_TypeDef*)  0x20;

	iface.PORTB = (_PORTx_TypeDef*) 0x18;
	iface.DDRB  = (_DDR_TypeDef*)   0x17;
	iface.PINB  = (_PINx_TypeDef*)  0x16;

	iface.PORTC = (_PORTx_TypeDef*) 0x15;
	iface.DDRC  = (_DDR_TypeDef*)   0x14;
	iface.PINC  = (_PINx_TypeDef*)  0x13;

	iface.PORTD = (_PORTx_TypeDef*) 0x12;
	iface.DDRD  = (_DDR_TypeDef*)   0x11;
	iface.PIND  = (_PINx_TypeDef*)  0x10;

	return &iface;
}
