#include "external_interrupts.h"

/*** Initialization function implementation ***/
_EXT_INT_Module EXT_INT_init(void) {
    _EXT_INT_Module module = {
        .EIFR = (_EIFR_TypeDef *)0x003C,
        .EIMSK = (_EIMSK_TypeDef *)0x003D,
        .EICRA = (_EICRA_TypeDef *)0x0060,
    };
    return module;
}
