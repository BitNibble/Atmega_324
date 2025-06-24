#ifndef ATMEGA324_RTC_H
#define ATMEGA324_RTC_H

#include <stdint.h>

/*** Base Types ***/
typedef volatile union {
	struct { uint8_t b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; } par;
	uint8_t var;
} _uint8_t;

typedef volatile union {
	struct {
		uint8_t rtic:1;
		uint8_t rtie:1;
		uint8_t :6;
	} par;
	uint8_t var;
} _RTICR_TypeDef;  // RTC Interrupt Control Register

typedef volatile union {
	struct {
		uint8_t rtcrun:1;
		uint8_t rtcen:1;
		uint8_t rtcreset:1;
		uint8_t :5;
	} par;
	uint8_t var;
} _RTCCR_TypeDef;  // RTC Control Register

typedef volatile union {
	struct {
		uint8_t rtcload:8;
	} par;
	uint8_t var;
} _RTCLR_TypeDef;  // RTC Load Register

typedef volatile union {
	struct {
		uint8_t rtccount:8;
	} par;
	uint8_t var;
} _RTCCR1_TypeDef;  // RTC Count Register (assuming 8-bit for simplicity)

/*** RTC Module Struct ***/
typedef struct {
	_RTICR_TypeDef* RTICR;  // Interrupt Control
	_RTCCR_TypeDef* RTCCR;  // Control
	_RTCLR_TypeDef* RTCLR;  // Load
	_RTCCR1_TypeDef* RTCCR1; // Count
} _RTC_Module;

#ifdef __cplusplus
extern "C" {
#endif

_RTC_Module* RTC_enable(void);

#ifdef __cplusplus
}
#endif

#endif // ATMEGA324_RTC_H
