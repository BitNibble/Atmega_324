#ifndef ATMEGA324_WDT_H
#define ATMEGA324_WDT_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

/*** Watchdog Timer Registers ***/

typedef volatile union {
	struct {
		uint8_t wdp0 :1;
		uint8_t wdp1 :1;
		uint8_t wdp2 :1;
		uint8_t wdp3 :1;
		uint8_t wde :1;
		uint8_t wdce :1;
		uint8_t :2;
	} par;
	uint8_t var;
} _WDTCR_TypeDef; // Watchdog Timer Control Register (WDTCSR on some MCUs)

/*** Watchdog Module ***/
typedef struct {
	_WDTCR_TypeDef* WDTCR;
} _WDT_Module;

#ifdef __cplusplus
extern "C" {
#endif

_WDT_Module* WDT_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_WDT_H
