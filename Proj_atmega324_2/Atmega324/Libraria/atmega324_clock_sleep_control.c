#include "clock_sleep_control.h"

/*** Initialization function implementation ***/
_CLOCK_SLEEP_Module CLOCK_SLEEP_init(void) {
    _CLOCK_SLEEP_Module module = {
        .CLKPR = (_CLKPR_TypeDef *)0x0061,
        .PRR   = (_PRR_TypeDef *)0x0064,
        .MCUCR = (_MCUCR_TypeDef *)0x0055,
        .SMCR  = (_SMCR_TypeDef *)0x0056,
    };
    return module;
}
