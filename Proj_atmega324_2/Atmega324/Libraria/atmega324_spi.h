#ifndef ATMEGA324_SPI_H
#define ATMEGA324_SPI_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

/*** SPI Registers ***/
typedef volatile union {
	struct {
		uint8_t spr0:1, spr1:1, cpha:1, cpol:1, mstr:1, dord:1, spe:1, spie:1;
	} par;
	uint8_t var;
} _SPCR_TypeDef; // 0x004C

typedef volatile union {
	struct {
		uint8_t spi2x:1, :5, wcol:1, spif:1;
	} par;
	uint8_t var;
} _SPSR_TypeDef; // 0x004D

typedef _uint8_t _SPDR_TypeDef; // 0x004E

/*** SPI Module Interface ***/
typedef struct {
	_SPCR_TypeDef* spcr;
	_SPSR_TypeDef* spsr;
	_SPDR_TypeDef* spdr;
} _SPI_Module;

#ifdef __cplusplus
extern "C" {
#endif

_SPI_Module* SPI_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_SPI_H
