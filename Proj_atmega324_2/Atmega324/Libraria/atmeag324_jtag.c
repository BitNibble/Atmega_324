#include "jtag.h"

/*** Initialization function implementation ***/
_JTAG_Module JTAG_init(void) {
    _JTAG_Module module = {
        .MCUCR = (_MCUCR_TypeDef *)0x0055,  // MCU Control Register
        .MCUSR = (_MCUSR_TypeDef *)0x0054,  // MCU Status Register
    };
    return module;
}
