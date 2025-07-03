/******************************************************************************
	BUFFER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     26062025
*******************************************************************************/
#ifndef _BUFFER_H_
	#define _BUFFER_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
#define BUFFvar char

/*** Typedef ***/
typedef struct {
	BUFFvar* orig;
	BUFFvar* head;
	BUFFvar* end;
}bufferparameter;

/*** Handler ***/
struct buffer
{
	bufferparameter par;
	void (*push)(bufferparameter* par, BUFFvar data);
	BUFFvar* (*raw)(bufferparameter* par);
	void (*flush)(bufferparameter* par);
};

typedef struct buffer BUFF;

/*** Global ***/
BUFF buff_enable(uint8_t size_buff, BUFFvar* buff);

#endif

/***EOF***/

