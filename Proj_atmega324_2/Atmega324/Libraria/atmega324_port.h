#ifndef ATMEGA324_PORT_H
#define ATMEGA324_PORT_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

/*** PORT Registers ***/

// PORTx Data Register (PORTA, PORTB, PORTC, PORTD)
typedef _uint8_t _PORTx_TypeDef;

// PORTx Data Direction Register (DDRA, DDRB, DDRC, DDRD)
typedef _uint8_t _DDR_TypeDef;

// PORTx Input Pins Address (PINA, PINB, PINC, PIND)
typedef _uint8_t _PINx_TypeDef;

/*** PORT Module Interface ***/
typedef struct {
	_PORTx_TypeDef* PORTA;
	_DDR_TypeDef*   DDRA;
	_PINx_TypeDef*  PINA;

	_PORTx_TypeDef* PORTB;
	_DDR_TypeDef*   DDRB;
	_PINx_TypeDef*  PINB;

	_PORTx_TypeDef* PORTC;
	_DDR_TypeDef*   DDRC;
	_PINx_TypeDef*  PINC;

	_PORTx_TypeDef* PORTD;
	_DDR_TypeDef*   DDRD;
	_PINx_TypeDef*  PIND;
} _PORT_Module;

#ifdef __cplusplus
extern "C" {
#endif

_PORT_Module* PORT_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_PORT_H
