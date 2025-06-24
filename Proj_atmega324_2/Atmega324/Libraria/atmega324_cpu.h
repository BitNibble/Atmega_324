#ifndef ATMEGA324_CPU_H
#define ATMEGA324_CPU_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

/*** CPU Registers ***/

typedef volatile union {
	struct {
		uint8_t carry :1;
		uint8_t zero :1;
		uint8_t negative :1;
		uint8_t two_complement_overflow :1;
		uint8_t sign :1;
		uint8_t half_carry :1;
		uint8_t bit_copy_storage :1;
		uint8_t interrupt_flag :1;
	} par;
	uint8_t var;
} _SREG_TypeDef; // Status Register

typedef volatile union {
	struct {
		uint8_t isc00 :1;
		uint8_t isc01 :1;
		uint8_t isc10 :1;
		uint8_t isc11 :1;
		uint8_t sm0 :1;
		uint8_t sm1 :1;
		uint8_t sm2 :1;
		uint8_t se :1;
	} par;
	uint8_t var;
} _MCUCR_TypeDef; // MCU Control Register

typedef volatile union {
	struct {
		uint8_t porf :1;
		uint8_t extrf :1;
		uint8_t borf :1;
		uint8_t wdrf :1;
		uint8_t jtrf :1;
		uint8_t isc2 :1;
		uint8_t :1;
		uint8_t :1;
	} par;
	uint8_t var;
} _MCUCSR_TypeDef; // MCU Control and Status Register

typedef volatile union {
	struct {
		uint8_t sm0 :1;
		uint8_t sm1 :1;
		uint8_t sm2 :1;
		uint8_t se :1;
		uint8_t :4;
	} par;
	uint8_t var;
} _SMCR_TypeDef; // Sleep Mode Control Register

/*** CPU Module ***/
typedef struct {
	_SREG_TypeDef* SREG;
	_MCUCR_TypeDef* MCUCR;
	_MCUCSR_TypeDef* MCUCSR;
	_SMCR_TypeDef* SMCR;
} _CPU_Module;

#ifdef __cplusplus
extern "C" {
#endif

_CPU_Module* CPU_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_CPU_H
