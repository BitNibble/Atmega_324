#ifndef JTAG_H
#define JTAG_H

#include <stdint.h>

/*** JTAG Interface Registers typedefs ***/

typedef volatile union {
    struct {
        uint8_t jtd:1;
        uint8_t :7;
    } par;
    uint8_t var;
} _MCUCR_TypeDef;

typedef volatile union {
    struct {
        uint8_t jtrf:1;
        uint8_t :7;
    } par;
    uint8_t var;
} _MCUSR_TypeDef;

/*** JTAG Module struct ***/
typedef struct {
    _MCUCR_TypeDef *MCUCR;
    _MCUSR_TypeDef *MCUSR;
} _JTAG_Module;

/*** Initialization function prototype ***/
_JTAG_Module JTAG_init(void);

#endif // JTAG_H
