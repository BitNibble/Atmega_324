#ifndef ATMEGA324_USART1_H
#define ATMEGA324_USART1_H

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

/*** USART1 Registers ***/
typedef volatile union {
	struct {
		uint8_t mpcm1:1, u2x1:1, upe1:1, dor1:1, fe1:1, udre1:1, txc1:1, rxc1:1;
	} par;
	uint8_t var;
} _UCSR1A_TypeDef; // 0x00C8

typedef volatile union {
	struct {
		uint8_t txb81:1, rxb81:1, ucsz12:1, txen1:1, rxen1:1, udrie1:1, txcie1:1, rxcie1:1;
	} par;
	uint8_t var;
} _UCSR1B_TypeDef; // 0x00C9

typedef volatile union {
	struct {
		uint8_t ucpol1:1, ucsz10:1, ucsz11:1, usbs1:1, upm10:1, upm11:1, umsel10:1, umsel11:1;
	} par;
	uint8_t var;
} _UCSR1C_TypeDef; // 0x00CA

typedef _uint8_t  _UBRR1L_TypeDef; // 0x00CC  
typedef _uint8_t  _UBRR1H_TypeDef; // 0x00CD  
typedef _uint8_t  _UDR1_TypeDef;   // 0x00CE

/*** USART1 Module Interface ***/
typedef struct {
	_UCSR1A_TypeDef* ucsr1a;
	_UCSR1B_TypeDef* ucsr1b;
	_UCSR1C_TypeDef* ucsr1c;
	_UBRR1L_TypeDef* ubrr1l;
	_UBRR1H_TypeDef* ubrr1h;
	_UDR1_TypeDef*   udr1;
} _USART1_Module;

#ifdef __cplusplus
extern "C" {
#endif

_USART1_Module* USART1_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_USART1_H
