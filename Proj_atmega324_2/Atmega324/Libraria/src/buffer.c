/******************************************************************************
	BUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 26062025
Comment:
	Buffer
******************************************************************************/
/*** File Library ***/
#include "buffer.h"
#include <stdio.h>
#include <string.h>

/*** Function declaration ***/
void BUFF_push(bufferparameter* par, BUFFvar data);
BUFFvar* BUFF_raw(bufferparameter* par);
void BUFF_flush(bufferparameter* par);

/*** Procedure & Function ***/
BUFF buff_enable( uint8_t size_buff, BUFFvar* buff )
{
	// OBJECT STRUCT
	BUFF ret;
	// inic VAR
	ret.par.orig = buff;
	ret.par.head = buff;
	ret.par.end = buff + ( size_buff );
	// function pointers
	ret.push = BUFF_push;
	ret.raw = BUFF_raw;
	ret.flush = BUFF_flush;
	return ret; // return copy
}

/*** Function definition ***/
void BUFF_push( bufferparameter* par, BUFFvar data ){
	BUFFvar* head; BUFFvar* next;
	head = par->head;
	if(data){
		if( head == par->end ){
			head = par->orig;
			next = head + 1;
		}else{
			next = head + 1;
		}
			*head = data;
			*next = 0;
			par->head = next;
	}
}

BUFFvar* BUFF_raw( bufferparameter* par ){
		return par->orig;
}

void BUFF_flush( bufferparameter* par ){
	BUFFvar* head;
	head = par->orig;
	par->head = head;
	*head = 0;
}

/***EOF***/

