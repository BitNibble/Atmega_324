#ifndef ATMEGA324_USART0_H
#define ATMEGA324_USART0_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

typedef volatile union {
	struct { _uint8_t l, h; } par;
	uint16_t var;
} _uint16_t;

/*** USART0 Registers ***/
typedef volatile union {
	struct {
		uint8_t mpcm0:1, u2x0:1, upe0:1, dor0:1, fe0:1, udre0:1, txc0:1, rxc0:1;
	} par;
	uint8_t var;
} _UCSR0A_TypeDef; // 0x00C0

typedef volatile union {
	struct {
		uint8_t txb80:1, rxb80:1, ucsz02:1, txen0:1, rxen0:1, udrie0:1, txcie0:1, rxcie0:1;
	} par;
	uint8_t var;
} _UCSR0B_TypeDef; // 0x00C1

typedef volatile union {
	struct {
		uint8_t ucpol0:1, ucsz00:1, ucsz01:1, usbs0:1, upm00:1, upm01:1, umsel00:1, umsel01:1;
	} par;
	uint8_t var;
} _UCSR0C_TypeDef; // 0x00C2

typedef _uint8_t  _UBRR0L_TypeDef; // 0x00C4  
typedef _uint8_t  _UBRR0H_TypeDef; // 0x00C5  
typedef _uint8_t  _UDR0_TypeDef;   // 0x00C6

/*** USART0 Module Interface ***/
typedef struct {
	_UCSR0A_TypeDef* ucsr0a;
	_UCSR0B_TypeDef* ucsr0b;
	_UCSR0C_TypeDef* ucsr0c;
	_UBRR0L_TypeDef* ubrr0l;
	_UBRR0H_TypeDef* ubrr0h;
	_UDR0_TypeDef*   udr0;
} _USART0_Module;

#ifdef __cplusplus
extern "C" {
#endif

_USART0_Module* USART0_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_USART0_H
