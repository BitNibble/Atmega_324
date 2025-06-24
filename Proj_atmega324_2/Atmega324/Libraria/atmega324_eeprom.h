#ifndef ATMEGA324_EEPROM_H
#define ATMEGA324_EEPROM_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

/*** EEPROM Registers ***/

typedef _uint8_t _EEDR_TypeDef;   // EEPROM Data Register (0x3D)
typedef _uint8_t _EEARL_TypeDef;  // EEPROM Address Register Low (0x3E)
typedef _uint8_t _EEARH_TypeDef;  // EEPROM Address Register High (0x3F)

typedef volatile union {
	struct {
		uint8_t eere:1, eepe:1, eempe:1, eerie:1, eemwe:1, :3;
	} par;
	uint8_t var;
} _EECR_TypeDef; // EEPROM Control Register (0x3C)

/*** EEPROM Module Interface ***/
typedef struct {
	_EECR_TypeDef*  eecr;
	_EEDR_TypeDef*  eedr;
	_EEARL_TypeDef* eearl;
	_EEARH_TypeDef* eearh;
} _EEPROM_Module;

#ifdef __cplusplus
extern "C" {
#endif

_EEPROM_Module* EEPROM_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_EEPROM_H
