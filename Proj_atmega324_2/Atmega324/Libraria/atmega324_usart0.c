#include "usart0.h"

static _USART0_Module iface;

_USART0_Module* USART0_enable(void) {
	iface.ucsr0a = (_UCSR0A_TypeDef*) 0xC0;
	iface.ucsr0b = (_UCSR0B_TypeDef*) 0xC1;
	iface.ucsr0c = (_UCSR0C_TypeDef*) 0xC2;
	iface.ubrr0l = (_UBRR0L_TypeDef*) 0xC4;
	iface.ubrr0h = (_UBRR0H_TypeDef*) 0xC5;
	iface.udr0   = (_UDR0_TypeDef*)   0xC6;

	return &iface;
}
