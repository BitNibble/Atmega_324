/*************************************************************************
	ATMEGA 324 TIMER HANDLERS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 324 at 8Mhz
*************************************************************************/
/*
** library
*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
/***/
#include "atmega324timer.h"
/*
** constant and macro
*/
#if  defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__)
	/**GLOBAL**/
	#define SYSTEM_REGISTER SREG
	#define GLOBAL_INTERRUPT_ENABLE 7
	/*** Interrupt sources 0 ***/
	#define TIMER_COUNTER0A_COMPARE_MATCH_INTERRUPT TIMER0_COMPA_vect
	#define TIMER_COUNTER0B_COMPARE_MATCH_INTERRUPT TIMER0_COMPB_vect
	#define TIMER_COUNTER0_OVERFLOW_INTERRUPT TIMER0_OVF_vect
	/*** Interrupt sources 1 ***/
	#define TIMER_COUNTER1A_COMPARE_MATCH_INTERRUPT TIMER1_COMPA_vect
	#define TIMER_COUNTER1B_COMPARE_MATCH_INTERRUPT TIMER1_COMPB_vect
	#define TIMER_COUNTER1_CAPTURE_EVENT_INTERRUPT TIMER1_CAPT_vect
	#define TIMER_COUNTER1_OVERFLOW_INTERRUPT TIMER1_OVF_vect
	/*** Interrupt sources 2 ***/
	#define TIMER_COUNTER2A_COMPARE_MATCH_INTERRUPT TIMER2_COMPA_vect
	#define TIMER_COUNTER2B_COMPARE_MATCH_INTERRUPT TIMER2_COMPB_vect
	#define TIMER_COUNTER2_OVERFLOW_INTERRUPT TIMER2_OVF_vect
	/***COMMON***/
	#define TIMER_COUNTER_ASYNCHRONOUS_STATUS_REGISTER ASSR
	#define TIMER_COUNTER_SPECIAL_FUNCTION_IO_REGISTER SFIOR
/*
** variable
*/
static TIMER_COUNTER0 timer0 = {0};
static uint8_t timer0_state;
static TIMER_COUNTER1 timer1 = {0};
static uint8_t timer1_state;
static TIMER_COUNTER2 timer2 = {0};
static uint8_t timer2_state;
/*
** procedure and function header
*/
void TIMER_COUNTER0_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER0_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER0_compareA(uint8_t compare);
void TIMER_COUNTER0_compareB(uint8_t compare);
void TIMER_COUNTER0_start(uint16_t prescaler);
void TIMER_COUNTER0_stop(void);
/******/
void TIMER_COUNTER1_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER1_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER1_compareA(uint16_t compare);
void TIMER_COUNTER1_compareB(uint16_t compare);
void TIMER_COUNTER1_start(uint16_t prescaler);
void TIMER_COUNTER1_stop(void);
/******/
void TIMER_COUNTER2_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER2_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER2_compareA(uint8_t compare);
void TIMER_COUNTER2_compareB(uint8_t compare);
void TIMER_COUNTER2_start(uint16_t prescaler);
void TIMER_COUNTER2_stop(void);
/*
** procedure and function
*/
TIMER_COUNTER0 TIMER_COUNTER0enable(uint8_t wavegenmode, uint8_t interrupt)
{
	
	timer0_state=0;
	// registers
	timer0.reg = tc0_instance();
	
	timer0.reg->ocr0a->var = 0XFF;
	timer0.reg->ocr0b->var = 0XFF;
	timer0.reg->tccr0a->var &= ~((1<<WGM00) | (1<<WGM01));
	timer0.reg->tccr0b->var &= ~(1<<WGM02);
	switch(wavegenmode){
		case 1: // PWM, Phase Correct
			timer0.reg->tccr0a->var|=(1<<WGM00);
			break;
		case 2: // CTC
			timer0.reg->tccr0a->var|=(1<<WGM01);
			break;
		case 3: // Fast PWM
			timer0.reg->tccr0a->var|=((1<<WGM00) | (1<<WGM01));
			break;
		case 5: // PWM, Phase Correct
			timer0.reg->tccr0b->var&=~((1<<FOC0A) | (1<<FOC0B));
			timer0.reg->tccr0a->var|=(1<<WGM00);
			timer0.reg->tccr0b->var|=(1<<WGM02);
			break;
		case 7: // Fast PWM
			timer0.reg->tccr0b->var&=~((1<<FOC0A) | (1<<FOC0B));
			timer0.reg->tccr0a->var|=((1<<WGM00) | (1<<WGM01));
			timer0.reg->tccr0b->var|=(1<<WGM02);
			break;
		default: // Normal
			break;
	}
	timer0.reg->timsk0->var &= ~((1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0));
	switch(interrupt){
		case 1:
			timer0.reg->timsk0->var|=(1<<TOIE0);
			break;
		case 2:
			timer0.reg->timsk0->var|=(1<<OCIE0A);
			break;
		case 3:
			timer0.reg->timsk0->var|=(1<<OCIE0B);
			break;
		case 4:
			timer0.reg->timsk0->var|=((1<<OCIE0A) | (1<<OCIE0B));
			break;
		case 5:
			timer0.reg->timsk0->var|=((1<<TOIE0) | (1<<OCIE0A) | (1<<OCIE0B));
			break;
		case 6:
			timer0.reg->timsk0->var|=((1<<TOIE0) | (1<<OCIE0A));
			break;
		case 7:
			timer0.reg->timsk0->var|=((1<<TOIE0) | (1<<OCIE0B));
			break;
		default:
			break;
	}
	timer0.compoutmodeA=TIMER_COUNTER0_compoutmodeA;
	timer0.compoutmodeB=TIMER_COUNTER0_compoutmodeB;
	timer0.compareA=TIMER_COUNTER0_compareA;
	timer0.compareB=TIMER_COUNTER0_compareB;
	timer0.start=TIMER_COUNTER0_start;
	timer0.stop=TIMER_COUNTER0_stop;

	return timer0;
}

TIMER_COUNTER0* TC0(void){ return &timer0; }

void TIMER_COUNTER0_start(uint16_t prescaler)
{
	uint8_t timer0_prescaler;
	if(timer0_state==0){ // oneshot
		timer0.reg->tcnt0->var=0X00;
		timer0_prescaler=0; // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clk T0S /(No prescaler)
			timer0_prescaler=(1<<CS00);
			break;
			case 8: // clk T0S /8 (From prescaler)
			timer0_prescaler=(1<<CS01);
			break;
			case 64: // clk T0S /64 (From prescaler)
			timer0_prescaler=((1<<CS01) | (1<<CS00));
			break;
			case 256: // clk T 0 S /256 (From prescaler)
			timer0_prescaler=(1<<CS02);
			break;
			case 1024: // clk T 0 S /1024 (From prescaler)
			timer0_prescaler=((1<<CS02) | (1<<CS00));
			break;
			case 3: // Ext Clock T0 pin falling edge
			timer0_prescaler=((1<<CS02) | (1<<CS01));
			break;
			case 5: // Ext Clock T0 pin rising edge
			timer0_prescaler=((1<<CS02) | (1<<CS01) | (1<<CS00));
			break;
			default: // clk T 0 S /1024 (From prescaler)
			timer0_prescaler=((1<<CS02) | (1<<CS00));
			break;
		}
		timer0.reg->tccr0b->var|=timer0_prescaler;
		cpu_instance()->sreg->par.i = 1;
		timer0_state=1;
	}
}
void TIMER_COUNTER0_compoutmodeA(uint8_t compoutmode)
{
	timer0.reg->tccr0a->var&=~((1<<COM0A1) | (1<<COM0A0));
	switch(compoutmode){ // see table 53, 54, 55 in datasheet for more information
		case 1: // Reserved
		// Toggle OC0 on compare match
		timer0.reg->tccr0a->var|=(1<<COM0A0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. 
		// Set OC0 on compare
		// match when down counting.
		// Clear OC0 on compare match
		timer0.reg->tccr0a->var|=(1<<COM0A1);
		break;
		case 3: // Set OC0 on compare match when up-counting. 
		// Clear OC0 on compare
		// match when down counting.
		// Set OC0 on compare match
		timer0.reg->tccr0a->var|=((1<<COM0A0) | (1<<COM0A1));
		break;
		default: // Normal port operation, OC0 disconnected.
		break;
	}
}
void TIMER_COUNTER0_compoutmodeB(uint8_t compoutmode)
{
	timer0.reg->tccr0a->var&=~((1<<COM0B1) | (1<<COM0B0));
	switch(compoutmode){ // see table 53, 54, 55 in datasheet for more information
		case 1: // Reserved
		// Toggle OC0 on compare match
		timer0.reg->tccr0a->var|=(1<<COM0B0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. 
		// Set OC0 on compare
		// match when down counting.
		// Clear OC0 on compare match
		timer0.reg->tccr0a->var|=(1<<COM0B1);
		break;
		case 3: // Set OC0 on compare match when up-counting. 
		// Clear OC0 on compare
		// match when down counting.
		// Set OC0 on compare match
		timer0.reg->tccr0a->var|=((1<<COM0B0) | (1<<COM0B1));
		break;
		default: // Normal port operation, OC0 disconnected.
		break;
	}
}
void TIMER_COUNTER0_compareA(uint8_t compare)
{
	timer0.reg->ocr0a->var=compare;
}
void TIMER_COUNTER0_compareB(uint8_t compare)
{
	timer0.reg->ocr0b->var=compare;
}
void TIMER_COUNTER0_stop(void)
{
	timer0.reg->tccr0b->var&=~((1<<CS02) | (1<<CS01) | (1<<CS00)); // No clock source. (Timer/Counter stopped)
	timer0_state=0;
}
/*****************************************************************************************/
TIMER_COUNTER1 TIMER_COUNTER1enable(uint8_t wavegenmode, uint8_t interrupt)
{
	timer1_state=0;
	// registers
	timer1.reg = tc1_instance();
	
	timer1.reg->ocr1a->var = 0XFFFF;
	timer1.reg->ocr1b->var = 0XFFFF;
	timer1.reg->tccr1a->var &= ~((1<<WGM11) | (1<<WGM10));
	timer1.reg->tccr1b->var &= ~((1<<WGM13) | (1<<WGM12));
	
	switch(wavegenmode){
		case 1: // PWM, Phase Correct, 8-bit
			timer1.reg->tccr1a->var|=(1<<WGM10);
			break;
		case 2:	// PWM, Phase Correct, 9-bit
			timer1.reg->tccr1a->var|=(1<<WGM11);
			break;
		case 3:	// PWM, Phase Correct, 10-bit
			timer1.reg->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			break;
		case 4:	// CTC OCR
			timer1.reg->tccr1b->var|=(1<<WGM12);
			break;
		case 5:	// Fast PWM, 8-bit
			timer1.reg->tccr1a->var|=(1<<WGM10);
			timer1.reg->tccr1b->var|=(1<<WGM12);
			break;
		case 6:	// Fast PWM, 9-bit
			timer1.reg->tccr1a->var|=(1<<WGM11);
			timer1.reg->tccr1b->var|=(1<<WGM12);
			break;
		case 7:	// Fast PWM, 10-bit
			timer1.reg->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			timer1.reg->tccr1b->var|=(1<<WGM12);
			break;
		case 8:	// PWM, Phase and Frequency Correct
			timer1.reg->tccr1b->var|=(1<<WGM13);
			break;
		case 9:	// PWM, Phase and Frequency Correct
			timer1.reg->tccr1c->var&=~((1<<FOC1A) | (1<<FOC1B));
			timer1.reg->tccr1a->var|=(1<<WGM10);
			timer1.reg->tccr1b->var|=(1<<WGM13);
			break;
		case 10: // PWM, Phase Correct
			timer1.reg->tccr1a->var|=(1<<WGM11);
			timer1.reg->tccr1b->var|=(1<<WGM13);
			break;
		case 11: // PWM, Phase Correct
			timer1.reg->tccr1c->var&=~((1<<FOC1A) | (1<<FOC1B));
			timer1.reg->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			timer1.reg->tccr1b->var|=(1<<WGM13);
			break;
		case 12: // CTC ICR
			timer1.reg->tccr1b->var|=((1<<WGM13) | (1<<WGM12));
			break;
		case 14: // Fast PWM
			timer1.reg->tccr1a->var|=(1<<WGM11);
			timer1.reg->tccr1b->var|=((1<<WGM13) | (1<<WGM12));
			break;
		case 15: // Fast PWM
			timer1.reg->tccr1c->var&=~((1<<FOC1A) | (1<<FOC1B));
			timer1.reg->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			timer1.reg->tccr1b->var|=((1<<WGM13) | (1<<WGM12));
			break;
		default: // Normal
			break;
	}
	timer1.reg->timsk1->var&=~((1<<ICIE1) | (1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1));
	switch(interrupt){
		case 1:
			timer1.reg->timsk1->var|=(1<<TOIE1);
			break;
		case 2:
			timer1.reg->timsk1->var|=(1<<OCIE1B);
			break;
		case 3:
			timer1.reg->timsk1->var|=(1<<OCIE1A);
		break;
			case 4:
			timer1.reg->timsk1->var|=(1<<ICIE1);
		break;
			case 6:
			timer1.reg->timsk1->var|=((1<<OCIE1B) | (1<<TOIE1));
			break;
		case 7:
			timer1.reg->timsk1->var|=((1<<OCIE1A) | (1<<TOIE1));
			break;
		case 8:
			timer1.reg->timsk1->var|=((1<<OCIE1A) | (1<<OCIE1B));
			break;
		case 9:
			timer1.reg->timsk1->var|=((1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1));
			break;
		default:
			break;
	}
	//
	timer1.compoutmodeA=TIMER_COUNTER1_compoutmodeA;
	timer1.compoutmodeB=TIMER_COUNTER1_compoutmodeB;
	timer1.compareA=TIMER_COUNTER1_compareA;
	timer1.compareB=TIMER_COUNTER1_compareB;
	timer1.start=TIMER_COUNTER1_start;
	timer1.stop=TIMER_COUNTER1_stop;

	return timer1;
}

TIMER_COUNTER1* TC1(void){ return &timer1; }

void TIMER_COUNTER1_start(uint16_t prescaler)
{
	uint8_t timer1_prescaler;
	if(timer1_state==0){ // oneshot
		timer1.reg->tcnt1->var=0X0000;
		timer1_prescaler=0; // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clkI/O/1 (No prescaling)
				timer1_prescaler=(1<<CS10);
				break;
			case 8: // clkI/O/8 (From prescaler)
				timer1_prescaler=(1<<CS11);
				break;
			case 64: // clkI/O/64 (From prescaler)
				timer1_prescaler=((1<<CS11) | (1<<CS10));
				break;
			case 256: // clkI/O/256 (From prescaler)
				timer1_prescaler=(1<<CS12);
				break;
			case 1024: // clkI/O/1024 (From prescaler)
				timer1_prescaler=((1<<CS12) | (1<<CS10));
				break;
			case 3: // External clock source on Tn pin. Clock on falling edge
				timer1_prescaler=((1<<CS12) | (1<<CS11));
				break;
			case 5: // External clock source on Tn pin. Clock on rising edge
				timer1_prescaler=((1<<CS12) | (1<<CS11) | (7<<CS10));
				break;
			default:
				timer1_prescaler=((1<<CS12) | (1<<CS10));
				break;
		}
		timer1.reg->tccr1b->var|=timer1_prescaler;
		cpu_instance()->sreg->par.i = 1;
		timer1_state=1;
	}
}
void TIMER_COUNTER1_compoutmodeA(uint8_t compoutmode)
{
	timer1.reg->tccr1a->var&=~((1<<COM1A1) | (1<<COM1A0));
	switch(compoutmode){ // see table 53, 54, 55 in datasheet for more information
		case 1: // Reserved
			// Toggle OC1A on compare match
			timer1.reg->tccr1a->var|=(1<<COM1A0);
			break;
		case 2: // Clear OC1A on compare match when up-counting. 
			// Set OC1A on compare
			// match when down counting.
			// Clear OC1A on compare match
			timer1.reg->tccr1a->var|=(1<<COM1A1);
			break;
		case 3: // Set OC1A on compare match when up-counting. 
			// Clear OC1 on compare
			// match when down counting.
			// Set OC1A on compare match
			timer1.reg->tccr1a->var|=((1<<COM1A0) | (1<<COM1A1));
			break;
		default: // Normal port operation, OC1A disconnected.
			break;
	}
}
void TIMER_COUNTER1_compoutmodeB(uint8_t compoutmode)
{
	timer1.reg->tccr1a->var&=~((1<<COM1B1) | (1<<COM1B0));
	switch(compoutmode){ // see table 53, 54, 55 in datasheet for more information
		case 1: // Reserved
			// Toggle OC1B on compare match
			timer1.reg->tccr1a->var|=(1<<COM1B0);
			break;
		case 2: // Clear OC1B on compare match when up-counting. 
			// Set OC1 on compare
			// match when down counting.
			// Clear OC1B on compare match
			timer1.reg->tccr1a->var|=(1<<COM1B1);
			break;
		case 3: // Set OC1B on compare match when up-counting. 
			// Clear OC1 on compare
			// match when down counting.
			// Set OC1 on compare match
			timer1.reg->tccr1a->var|=((1<<COM1B0) | (1<<COM1B1));
			break;
		default: // Normal port operation, OC1B disconnected.
			break;
	}
}
void TIMER_COUNTER1_compareA(uint16_t compare)
{
	// TOP VALUE
	timer1.reg->ocr1a->var=compare;
}
void TIMER_COUNTER1_compareB(uint16_t compare)
{
	timer1.reg->ocr1b->var=compare;
}
void TIMER_COUNTER1_stop(void)
/*
	stops timer by setting prescaler to zero
*/
{
	timer1.reg->tccr1b->var&=~((1<<CS12) | (1<<CS11) | (1<<CS10)); // No clock source. (Timer/Counter stopped)
	timer1_state=0;
}
/*****************************************************************************************/
TIMER_COUNTER2 TIMER_COUNTER2enable(unsigned char wavegenmode, unsigned char interrupt)
{
	timer2_state=0;
	// registers
	timer2.reg = tc2_instance();

	timer2.reg->ocr2a->var = 0XFF;
	timer2.reg->ocr2b->var = 0XFF;
	timer2.reg->tccr2a->var &= ~((1<<WGM20) | (1<<WGM21));
	timer2.reg->tccr2b->var &= ~(1<<WGM22);
	
	switch(wavegenmode){
		case 1: // PWM, Phase Correct
			timer2.reg->tccr2a->var|=(1<<WGM20);
			break;
		case 2: // CTC
			timer2.reg->tccr2a->var|=(1<<WGM21);
			break;
		case 3: // Fast PWM
			timer2.reg->tccr2a->var|=((1<<WGM20) | (1<<WGM21));
			break;
		case 5: // PWM, Phase Correct
			timer2.reg->tccr2b->var&=~((1<<FOC2A) | (1<<FOC2B));
			timer2.reg->tccr2a->var|=(1<<WGM20);
			timer2.reg->tccr2b->var|=(1<<WGM22);
			break;
		case 7: // Fast PWM
			timer2.reg->tccr2b->var&=~((1<<FOC2A) | (1<<FOC2B));
			timer2.reg->tccr2a->var|=((1<<WGM20) | (1<<WGM21));
			timer2.reg->tccr2b->var|=(1<<WGM22);
			break;
		default: //// Normal
			break;
	}
	timer2.reg->timsk2->var &= ~((1<<TOIE2) | (1<<OCIE2A) | (1<<OCIE2B));
	switch(interrupt){
		case 1:
			timer2.reg->timsk2->var|=(1<<TOIE2);
			break;
		case 2:
			timer2.reg->timsk2->var|=(1<<OCIE2A);
			break;
		case 3:
			timer2.reg->timsk2->var|=(1<<OCIE2B);
			break;
		case 4:
			timer2.reg->timsk2->var|=((1<<OCIE2A) | (1<<OCIE2B));
			break;
		case 5:
			timer2.reg->timsk2->var|=((1<<OCIE2A) | (1<<OCIE2B) | (1<<TOIE2));
			break;
		case 6:
			timer2.reg->timsk2->var|=((1<<TOIE2) | (1<<OCIE2A));
			break;
		case 7:
			timer2.reg->timsk2->var|=((1<<TOIE2) | (1<<OCIE2B));
			break;
		default:
			break;
	}
	timer2.compoutmodeA=TIMER_COUNTER2_compoutmodeA;
	timer2.compoutmodeB=TIMER_COUNTER2_compoutmodeB;
	timer2.compareA=TIMER_COUNTER2_compareA;
	timer2.compareB=TIMER_COUNTER2_compareB;
	timer2.start=TIMER_COUNTER2_start;
	timer2.stop=TIMER_COUNTER2_stop;

	return timer2;
}

TIMER_COUNTER2* TC2(void){ return &timer2; }

void TIMER_COUNTER2_start(uint16_t prescaler)
{
	uint8_t timer2_prescaler;
	if(timer2_state==0){ // oneshot
		timer2.reg->tcnt2->var=0X00;
		timer2_prescaler=0; // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clkI/O/(No prescaling)
				timer2_prescaler=(1<<CS20);
				break;
			case 8: // clkI/O/8 (From prescaler)
				timer2_prescaler=(1<<CS21);
				break;
			case 32: // clkI/O/32 (From prescaler)
				timer2_prescaler=((1<<CS21) | (1<<CS20));
				break;
			case 64: // clkI/O/64 (From prescaler)
				timer2_prescaler=(1<<CS22);
				break;
			case 128: // clkI/O/128 (From prescaler)
				timer2_prescaler=((1<<CS22) | (1<<CS20));
				break;
			case 256: // clkI/O/256 (From prescaler)
				timer2_prescaler=((1<<CS22) | (1<<CS21));
				break;
			case 1024: // clkI/O/1024 (From prescaler)
				timer2_prescaler=((1<<CS22) | (1<<CS21) | (1<<CS20));
				break;
			default:
				timer2_prescaler=((1<<CS22) | (1<<CS21) | (1<<CS20));
				break;
		}
		timer2.reg->tccr2b->var|=timer2_prescaler;
		cpu_instance()->sreg->par.i = 1;
		timer2_state=1;
	}
}
void TIMER_COUNTER2_compoutmodeA(uint8_t compoutmode)
{
	timer2.reg->tccr2a->var &= ~((1<<COM2A0) | (1<<COM2A1));
	switch(compoutmode){ // see table 53, 54, 55 in datasheet for more information
		case 1: // Reserved
			// Toggle OC2 on compare match
			timer2.reg->tccr2a->var|=(1<<COM2A0);
			break;
		case 2: // Clear OC2 on compare match when up-counting. 
			// Set OC2 on compare
			// match when down counting.
			// Clear OC2 on compare match
			timer2.reg->tccr2a->var|=(1<<COM2A1);
			break;
		case 3: // Set OC2 on compare match when up-counting. 
			// Clear OC2 on compare
			// match when down counting.
			// Set OC2 on compare match
			timer2.reg->tccr2a->var|=(1<<COM2A0) | (1<<COM2A1);
			break;
		default: // Normal port operation, OC2 disconnected.
			break;
	}
}
void TIMER_COUNTER2_compoutmodeB(uint8_t compoutmode)
{
	timer2.reg->tccr2a->var&=~((1<<COM2B0) | (1<<COM2B1));
	switch(compoutmode){ // see table 53, 54, 55 in datasheet for more information
		case 1: // Reserved
			// Toggle OC2 on compare match
			timer2.reg->tccr2a->var|=(1<<COM2B0);
			break;
		case 2: // Clear OC2 on compare match when up-counting. 
			// Set OC2 on compare
			// match when downcounting.
			// Clear OC2 on compare match
			timer2.reg->tccr2a->var|=(1<<COM2B1);
			break;
		case 3: // Set OC2 on compare match when up-counting. 
			// Clear OC2 on compare
			// match when downcounting.
			// Set OC2 on compare match
			timer2.reg->tccr2a->var|=(1<<COM2B0) | (1<<COM2B1);
			break;
		default: // Normal port operation, OC2 disconnected.
			break;
	}
}
void TIMER_COUNTER2_compareA(uint8_t compare)
{
	timer2.reg->ocr2a->var=compare;
}
void TIMER_COUNTER2_compareB(uint8_t compare)
{
	timer2.reg->ocr2b->var=compare;
}
void TIMER_COUNTER2_stop(void)
{
	timer2.reg->tccr2b->var &= ~((1<<CS22) | (1<<CS21) | (1<<CS20)); // No clock source. (Timer/Counter stopped)
	timer2_state=0;
}
#else
	#error "Atmega324timer only supports Atemaga 324A Sorry!!"
#endif
/***EOF***/

