#ifndef ATMEGA324_TWI_H
#define ATMEGA324_TWI_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

/*** TWI Registers ***/
typedef volatile union {
	struct {
		uint8_t twie:1, :1, twen:1, twwc:1, twsto:1, twsta:1, twea:1, twint:1;
	} par;
	uint8_t var;
} _TWCR_TypeDef; // 0x0056

typedef volatile union {
	struct {
		uint8_t twps0:1, twps1:1, :1, twbr:5;
	} par;
	uint8_t var;
} _TWSR_TypeDef; // 0x0051

typedef _uint8_t _TWBR_TypeDef; // 0x0050
typedef _uint8_t _TWDR_TypeDef; // 0x0053
typedef _uint8_t _TWAR_TypeDef; // 0x0052
typedef _uint8_t _TWAMR_TypeDef; // 0x0054

/*** TWI Module Interface ***/
typedef struct {
	_TWBR_TypeDef* twbr;
	_TWSR_TypeDef* twsr;
	_TWAR_TypeDef* twar;
	_TWDR_TypeDef* twdr;
	_TWCR_TypeDef* twcr;
	_TWAMR_TypeDef* twamr;
} _TWI_Module;

#ifdef __cplusplus
extern "C" {
#endif

_TWI_Module* TWI_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_TWI_H
