#include "usart1.h"

static _USART1_Module iface;

_USART1_Module* USART1_enable(void) {
	iface.ucsr1a = (_UCSR1A_TypeDef*) 0xC8;
	iface.ucsr1b = (_UCSR1B_TypeDef*) 0xC9;
	iface.ucsr1c = (_UCSR1C_TypeDef*) 0xCA;
	iface.ubrr1l = (_UBRR1L_TypeDef*) 0xCC;
	iface.ubrr1h = (_UBRR1H_TypeDef*) 0xCD;
	iface.udr1   = (_UDR1_TypeDef*)   0xCE;

	return &iface;
}
