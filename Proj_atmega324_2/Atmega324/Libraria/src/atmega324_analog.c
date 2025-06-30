/*************************************************************************
Title:    Interrupt ANALOG INPUT
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Date:     30062025
*************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdarg.h>
#include <inttypes.h>

#include "atmega324_analog.h"

#define MAX_CHANNEL 8
#define GLOBAL_INTERRUPT_ENABLE 7
#define MUX_MASK 31
#define ANALOG_INTERRUPT ADC_vect

static ANALOG analog;
static volatile int ADC_VALUE[MAX_CHANNEL] = {0};
static volatile int ADC_CHANNEL[MAX_CHANNEL] = {0};
volatile int ADC_N_CHANNEL;
volatile int ADC_SELECTOR;
volatile int adc_sample;
volatile int adc_tmp;
volatile unsigned char adc_n_sample;

int ANALOG_read(int selection);

ANALOG ANALOG_enable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... )
{
	va_list list;
	int i;
	
	cpu_reg()->sreg->var &= ~(1<<GLOBAL_INTERRUPT_ENABLE);
	
	ADC_N_CHANNEL = n_channel;
	ADC_SELECTOR = 0;
	adc_n_sample = 0;
	// V-table
	analog.read = ANALOG_read;
	/******/
	adc_reg()->admux->var &= ~(3<<REFS0);
	switch( Vreff ){
		case 0: //AREF, Internal Vref turned off
			analog.VREFF = 0;
			break;
		case 1: //AVCC with external capacitor at AREF pin
			adc_reg()->admux->var |= (1<<REFS0);
			analog.VREFF = 1;
			break;
		case 2: //Internal 1.1V Voltage Reference with external capacitor at AREF pin
			adc_reg()->admux->var |= (1<<REFS1);
			analog.VREFF = 2;
			break;
		case 3: //Internal 2.56V Voltage Reference with external capacitor at AREF pin
			adc_reg()->admux->var |= (3<<REFS0);
			analog.VREFF = 3;
			break;
		default:
			analog.VREFF = 0;
			break;
	}
	//
	adc_reg()->admux->var &= ~(1<<ADLAR);
	/******/
	va_start(list, n_channel);
	for( i=0; i < n_channel; i++ ) {
		ADC_CHANNEL[i] = va_arg(list, int);
	}
	va_end(list);
	adc_reg()->admux->var &= ~MUX_MASK;
	adc_reg()->admux->var |= (MUX_MASK & ADC_CHANNEL[ADC_SELECTOR]);
	/******/
	adc_reg()->adcsra->var |= (1 << ADEN);
	adc_reg()->adcsra->var |= (1 << ADSC);
	adc_reg()->adcsra->var &= ~(1 << ADATE);
	adc_reg()->adcsrb->var &= ~(7 << ADTS0);
	adc_reg()->adcsra->var |= (1 << ADIE);
	/******/
	adc_reg()->adcsra->var &= ~(7 << ADPS0);
	switch( Divfactor ) {
		case 2://1
			analog.DIVISION_FACTOR = 2;
			break;
		case 4://2
			adc_reg()->adcsra->var |= (1 << ADPS1);
			analog.DIVISION_FACTOR = 4;
			break;
		case 8://3
			adc_reg()->adcsra->var |= (3 << ADPS0);
			analog.DIVISION_FACTOR = 8;
			break;
		case 16://4
			adc_reg()->adcsra->var |= (1 << ADPS2);
			analog.DIVISION_FACTOR = 16;
			break;
		case 32://5
			adc_reg()->adcsra->var |= (5 << ADPS0);
			analog.DIVISION_FACTOR = 32;
			break;
		case 64://6
			adc_reg()->adcsra->var |= (3 << ADPS1);
			analog.DIVISION_FACTOR = 64;
			break;
		case 128://7
			adc_reg()->adcsra->var |= (7 << ADPS0);
			analog.DIVISION_FACTOR = 128;
			break;
		default:
			adc_reg()->adcsra->var |= (7 << ADPS0);
			analog.DIVISION_FACTOR = 128;
			break;
	}
	cpu_reg()->sreg->var |= (1 << GLOBAL_INTERRUPT_ENABLE);
	/******/
	return analog;
}
int ANALOG_read(int selection)
{
	uint8_t ADSC_FLAG;
	ADSC_FLAG = (1 << ADSC);
	if( !(adc_reg()->adcsra->var & ADSC_FLAG) ) {
		/***/
		adc_reg()->adcsra->var |= (1 << ADSC);
	}
	return ADC_VALUE[selection];
}

ISR(ANALOG_INTERRUPT)
{
	adc_tmp = ADCL;
	adc_tmp |= (ADCH << 8);
	if(adc_n_sample < (1 << ADC_NUMBER_SAMPLE)){
		adc_n_sample++;
		adc_sample += adc_tmp;
	}else{
		ADC_VALUE[ADC_SELECTOR] = adc_sample >> ADC_NUMBER_SAMPLE;
		adc_n_sample = adc_sample = 0;
		
		if(ADC_SELECTOR < ADC_N_CHANNEL)
			ADC_SELECTOR++;
		else
			ADC_SELECTOR = 0;
		adc_reg()->admux->var &= ~MUX_MASK;
		adc_reg()->admux->var |= (ADC_CHANNEL[ADC_SELECTOR] & MUX_MASK);
	}
}

/***EOF***/

