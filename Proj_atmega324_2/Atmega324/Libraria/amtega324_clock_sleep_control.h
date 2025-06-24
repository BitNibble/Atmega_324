#ifndef CLOCK_SLEEP_CONTROL_H
#define CLOCK_SLEEP_CONTROL_H

#include <stdint.h>

/*** Clock and Sleep Control Register typedefs ***/

typedef volatile union {
    struct {
        uint8_t clkps0:1;
        uint8_t clkps1:1;
        uint8_t clkps2:1;
        uint8_t clkps3:1;
        uint8_t clkpce:1;
        uint8_t :3;
    } par;
    uint8_t var;
} _CLKPR_TypeDef;

typedef volatile union {
    struct {
        uint8_t pradc:1;
        uint8_t prusart0:1;
        uint8_t prusart1:1;
        uint8_t prspi:1;
        uint8_t prtim0:1;
        uint8_t prtim1:1;
        uint8_t prtim2:1;
        uint8_t prtim3:1;
    } par;
    uint8_t var;
} _PRR_TypeDef;

typedef volatile union {
    struct {
        uint8_t isc00:1;
        uint8_t isc01:1;
        uint8_t isc10:1;
        uint8_t isc11:1;
        uint8_t sm1:1;
        uint8_t sm0:1;
        uint8_t se:1;
        uint8_t :1;
    } par;
    uint8_t var;
} _MCUCR_TypeDef;

typedef volatile union {
    struct {
        uint8_t sm2:1;
        uint8_t sm1:1;
        uint8_t sm0:1;
        uint8_t :5;
    } par;
    uint8_t var;
} _SMCR_TypeDef;

/*** Clock and Sleep Control Module struct ***/
typedef struct {
    _CLKPR_TypeDef *CLKPR;
    _PRR_TypeDef  *PRR;
    _MCUCR_TypeDef *MCUCR;
    _SMCR_TypeDef  *SMCR;
} _CLOCK_SLEEP_Module;

/*** Initialization function prototype ***/
_CLOCK_SLEEP_Module CLOCK_SLEEP_init(void);

#endif // CLOCK_SLEEP_CONTROL_H
