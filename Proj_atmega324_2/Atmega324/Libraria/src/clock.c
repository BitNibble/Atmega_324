/*************************************************************************
	CLOCK
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     31062025
*************************************************************************/
/*** File Library ***/
#include "clock.h"

/*** File Constant & Macro ***/

/*** File Variable ***/
static CLOCK_TIME time = {0};
static char CLOCK_tmp[9] = {0};

/*** File Header ***/
void CLOCK_set(uint8_t hour, uint8_t minute, uint8_t second);
void CLOCK_increment(void);
void CLOCK_decrement(void);
char* CLOCK_show(void);

/*** Procedure & Function ***/
CLOCK CLOCK_enable(uint8_t hour, uint8_t minute, uint8_t second)
{
	CLOCK clock;
	(hour < 24) ? time.hour = hour : (void) hour;  
	(minute < 60) ? time.minute = minute : (void) minute;
	(second < 60) ? time.second = second : (void) second;
	clock.set = CLOCK_set;
	clock.increment = CLOCK_increment;
	clock.show = CLOCK_show;
	return clock;
}
void CLOCK_set(uint8_t hour, uint8_t minute, uint8_t second)
{
	(hour < 24) ? time.hour = hour : (void) hour;
	(minute < 60) ? time.minute = minute : (void) minute;
	(second < 60) ? time.second = second : (void) second;
}
void CLOCK_increment(void)
{
	time.second++;
	if(time.second > 59){
		time.minute++;
		time.second = 0;
		if(time.minute > 59){
			time.hour++;
			time.minute = 0;
			switch (CLOCK_HORA){
				case 24:
					if(time.hour > 23)
						time.hour = 0;
				break;
				case 12:
					if (time.hour > 12)
						time.hour = 1;
				break;
				default:
					if(time.hour > 23)
						time.hour = 0;
				break;
			}
		}
	}
}

void CLOCK_decrement(void)
{
	time.second--;
	if(time.second < 0){
		time.minute--;
		time.second = 59;
		if(time.minute < 0){
			time.hour--;
			time.minute = 59;
			switch (CLOCK_HORA){
				case 24:
					if(time.hour < 0)
						time.hour= 23;
				break;
				case 12:
					if (time.hour < 1)
						time.hour = 12;
				break;
				default:
					if(time.hour < 0)
						time.hour = 23;
				break;
			}
		}
	}		
}

char* CLOCK_show(void)
{
	uint8_t tmp;
	CLOCK_tmp[8] = '\0';
	CLOCK_tmp[7] = time.second % 10 + '0';
	tmp = time.second / 10;
	CLOCK_tmp[6] = tmp % 10 + '0';
	CLOCK_tmp[5] = ':';
	CLOCK_tmp[4] = time.minute % 10 + '0';
	tmp = time.minute / 10;
	CLOCK_tmp[3] = tmp % 10 + '0';
	CLOCK_tmp[2] = ':';
	CLOCK_tmp[1] = time.hour % 10 + '0';
	tmp = time.hour / 10;
	CLOCK_tmp[0] = tmp % 10 + '0';
	return CLOCK_tmp;
}

/***EOF***/

