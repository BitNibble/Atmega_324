#ifndef EXTERNAL_INTERRUPTS_H
#define EXTERNAL_INTERRUPTS_H

#include <stdint.h>

/*** External Interrupt Registers typedefs ***/

typedef volatile union {
    struct {
        uint8_t intf0:1;
        uint8_t intf1:1;
        uint8_t intf2:1;
        uint8_t intf3:1;
        uint8_t :4;
    } par;
    uint8_t var;
} _EIFR_TypeDef;

typedef volatile union {
    struct {
        uint8_t int0:1;
        uint8_t int1:1;
        uint8_t int2:1;
        uint8_t int3:1;
        uint8_t :4;
    } par;
    uint8_t var;
} _EIMSK_TypeDef;

typedef volatile union {
    struct {
        uint8_t isc00:1;
        uint8_t isc01:1;
        uint8_t isc10:1;
        uint8_t isc11:1;
        uint8_t isc20:1;
        uint8_t isc21:1;
        uint8_t isc30:1;
        uint8_t isc31:1;
    } par;
    uint8_t var;
} _EICRA_TypeDef;

/*** External Interrupt Module struct ***/
typedef struct {
    _EIFR_TypeDef *EIFR;
    _EIMSK_TypeDef *EIMSK;
    _EICRA_TypeDef *EICRA;
} _EXT_INT_Module;

/*** Initialization function prototype ***/
_EXT_INT_Module EXT_INT_init(void);

#endif // EXTERNAL_INTERRUPTS_H
