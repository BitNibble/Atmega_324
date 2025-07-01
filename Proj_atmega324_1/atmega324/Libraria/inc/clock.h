/************************************************************************
	CLOCK
Author:   <sergio.salazar.santos@gmail.com>
Hardware: all
Date:     31106025
************************************************************************/
#ifndef _CLOCK_H_
	#define _CLOCK_H_

/*** Global Library ***/
#include <stdint.h>
#include <inttypes.h>

/*** Global Constant & Macro ***/
#define CLOCK_HORA 24

/*** Global Variable ***/
typedef volatile struct {
	int8_t hour;
	int8_t minute;
	int8_t second;
} RELOGIO_TIME;

struct clck{
	void (*set)(uint8_t hour, uint8_t minute, uint8_t second);
	void (*increment)(void);
	char* (*show)(void);
};
typedef struct clck CLOCK;

/*** Global Header ***/
CLOCK CLOCK_enable(uint8_t hour, uint8_t minute, uint8_t second);

#endif

/***EOF***/

