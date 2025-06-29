/*************************************************************************
Title:    Interrupt ANALOG INPUT
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Comment:
*************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdarg.h>
#include <inttypes.h>

#include "atmega324analog.h"

#if defined(__AVR_ATmega324A__)

#define MAX_CHANNEL 8

#define GLOBAL_INTERRUPT_ENABLE 7
#define ADC_SELECT ADMUX
#define ADC_CONTROL ADCSRA
#define ADC_TRIGGER ADCSRB
#define DIGITAL_INPUT_DISABLE_REGISTER DIDR0
#define MUX_MASK 31
#define ANALOG_INTERRUPT ADC_vect

static ANALOG analog;
static volatile int ADC_VALUE[MAX_CHANNEL];
static volatile int ADC_CHANNEL_GAIN[MAX_CHANNEL];
volatile int ADC_N_CHANNEL;
volatile int ADC_SELECTOR;
volatile int adc_sample;
volatile int adc_tmp;
volatile unsigned char adc_n_sample;

int ANALOG_read(int selection);

ANALOG ANALOGenable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... )
{
	uint8_t tSREG;
	va_list list;
	int i;
	
	tSREG=SREG;
	SREG&=~(1<<GLOBAL_INTERRUPT_ENABLE);
	
	ADC_N_CHANNEL=n_channel;
	ADC_SELECTOR=0;
	adc_n_sample=0;
	// V-table
	analog.read=ANALOG_read;
	/******/
	ADC_SELECT&=~(3<<REFS0);
	switch( Vreff ){
		case 0: //AREF, Internal Vref turned off
			analog.VREFF=0;
			break;
		case 1: //AVCC with external capacitor at AREF pin
			ADC_SELECT|=(1<<REFS0);
			analog.VREFF=1;
			break;
		case 2: //Internal 1.1V Voltage Reference with external capacitor at AREF pin
			ADC_SELECT|=(1<<REFS1);
			analog.VREFF=2;
			break;
		case 3: //Internal 2.56V Voltage Reference with external capacitor at AREF pin
			ADC_SELECT|=(3<<REFS0);
			analog.VREFF=3;
			break;
		default:
			analog.VREFF=0;
			break;
	}
	//
	ADC_SELECT&=~(1<<ADLAR);
	/******/
	va_start(list, n_channel);
	for(i=0;i<n_channel;i++){
		ADC_CHANNEL_GAIN[i] = va_arg(list, int);
	}
	va_end(list);
	ADC_SELECT&=~MUX_MASK;
	ADC_SELECT|=(MUX_MASK & ADC_CHANNEL_GAIN[ADC_SELECTOR]);
	/******/
	ADC_CONTROL|=(1<<ADEN);
	ADC_CONTROL|=(1<<ADSC);
	ADC_CONTROL&=~(1<<ADATE);
	ADC_TRIGGER&=~(7<<ADTS0);
	ADC_CONTROL|=(1<<ADIE);
	/******/
	ADC_CONTROL&=~(7<<ADPS0);
	switch( Divfactor ){
		case 2://1
			analog.DIVISION_FACTOR=2;
			break;
		case 4://2
			ADC_CONTROL|=(1<<ADPS1);
			analog.DIVISION_FACTOR=4;
			break;
		case 8://3
			ADC_CONTROL|=(3<<ADPS0);
			analog.DIVISION_FACTOR=8;
			break;
		case 16://4
			ADC_CONTROL|=(1<<ADPS2);
			analog.DIVISION_FACTOR=16;
			break;
		case 32://5
			ADC_CONTROL|=(5<<ADPS0);
			analog.DIVISION_FACTOR=32;
			break;
		case 64://6
			ADC_CONTROL|=(3<<ADPS1);
			analog.DIVISION_FACTOR=64;
			break;
		case 128://7
			ADC_CONTROL|=(7<<ADPS0);
			analog.DIVISION_FACTOR=128;
			break;
		default:
			ADC_CONTROL|=(7<<ADPS0);
			analog.DIVISION_FACTOR=128;
			break;
	}
	SREG=tSREG;
	SREG|=(1<<GLOBAL_INTERRUPT_ENABLE);
	/******/
	return analog;
}
int ANALOG_read(int selection)
{
	uint8_t ADSC_FLAG;
	ADSC_FLAG=(1<<ADSC);
	if( !(ADC_CONTROL & ADSC_FLAG) ){
		//ADC_SELECT
		/***/
		ADC_CONTROL|=(1<<ADSC);
	}
	return ADC_VALUE[selection];
}

ISR(ANALOG_INTERRUPT)
{
	adc_tmp=ADCL;
	adc_tmp|=(ADCH<<8);
	if(adc_n_sample < (1<<ADC_NUMBER_SAMPLE)){
		adc_n_sample++;
		adc_sample+=adc_tmp;
	}else{
		ADC_VALUE[ADC_SELECTOR]=adc_sample>>ADC_NUMBER_SAMPLE;
		adc_n_sample=adc_sample=0;
		
		if(ADC_SELECTOR < ADC_N_CHANNEL)
			ADC_SELECTOR++;
		else
			ADC_SELECTOR=0;
		ADC_SELECT &= ~MUX_MASK;
		ADC_SELECT |= (ADC_CHANNEL_GAIN[ADC_SELECTOR] & MUX_MASK);
	}
}
#else
	#error "Not ATmega 324A"

#endif
/***EOF***/

