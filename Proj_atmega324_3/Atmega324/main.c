/***************************************************************************
	Wavegen
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Created:  20/03/2018 18:35:21
Hardware: Atmega324A
	-PORTC - LCD
	-PORTD - HC05 blue tooth (usart0)
 ***************************************************************************/
//Good practice initialize
#define F_CPU 16000000UL
/******/
#include <stdio.h>
#include <string.h>
#include "atmega324_analog.h"
#include "atmega_eeprom.h"
#include "atmega324_timer.h"
#include "atmega324_usart0.h"
#include "atmega324_usart1.h"
#include "keypad.h"
#include "lcd.h"
#include "function.h"
#include "watch.h"
#include "clock.h"

volatile uint16_t counter = 0;
char* uartreceive = NULL; // capture

/*** Declaration ***/
void PORTINIT(void);
/*** Program Cycle ***/
int main(void)
{
/*** Inic ***/
PORTINIT();
/*** Handlers ***/
tc1_enable(4,3);// 4->CTC ; 3->TIMER1_COMPA_vect
lcd0_enable(&DDRC,&PINC,&PORTC);
func_enable();
watch_enable();
adc_enable( 1, 128, 1, 0 );
usart0_enable(38400,8,1,NONE);
/******/
char uartmsg[UART0_RX_BUFFER_SIZE] = {0}; // One shot
char uartmsgprint[UART0_RX_BUFFER_SIZE] = {0}; // triggered
char adc_read[32] = {0}; // One shot
/******/
tc1()->compareA(62499);
tc1()->start(256);
watch()->preset(0,0,0);
SPCR0 = 0x00;
/******/
while (1)
{
	usart0_messageprint( usart0(), uartmsg, uartmsgprint, "\r\n");
	
	lcd0()->gotoxy(0,0);
	lcd0()->putch(':');
	lcd0()->string_size(uartmsgprint, 11);
	if ( snprintf(adc_read, 31, "an: %d", adc()->read(0)) > 0 ) {
		lcd0()->gotoxy(1,12);
		lcd0()->string_size(adc_read, 8);
	}	
	lcd0()->gotoxy(3,12);
	lcd0()->string_size( watch()->show(), 8 );
}}
/***Prototypes***/
void PORTINIT(void){
	gpiod_reg()->ddr->var = (1<<4);
	gpiod_reg()->port->var = (1<<4);
};
/***Interrupts***/
ISR(TIMER1_COMPA_vect)
{
	gpiod_reg()->port->par.b4 ^= 1;
	WATCH_increment();
}

/***EOF***/

