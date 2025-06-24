/*********************************************************
	ATMEGA 324 MAPPING
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date: 30042023
Comment:
	Virtual Image Atmega 324 mapping.
**********************************************************/
/*** File Library ***/
#include "atmega324mapping.h"

/*** File Define & Macro ***/

/*** File Header ***/
uint16_t ReadHLByte(_uint16_t reg);
uint16_t ReadLHByte(_uint16_t reg);
_uint16_t WriteHLByte(uint16_t val);
_uint16_t WriteLHByte(uint16_t val);
uint16_t SwapByte(uint16_t num);

/*** Procedure & Function ***/
ATMEGA324 ATMEGA324enable(void){ 
	ATMEGA324 ret;
	// GPWR
	ret.gpwr = (_GPW_TypeDef*) Atmega324_GPW;
	// AC
	ret.ac.reg = (Atmega324AnalogComparator_TypeDef*) Atmega324AnalogComparator_Address;
	// ADC
	ret.adc.reg = (Atmega324AnalogToDigitalConverter_TypeDef*) Atmega324AnalogToDigitalConverter_Address;
	#if defined(_ATMEGA324ANALOG_H_)
		ret.adc.enable = ANALOGenable;
	#endif
	// BOOT
	ret.boot_load.reg = (Atmega324BootLoader_TypeDef*) Atmega324BootLoader_Address;
	// CPU
	ret.cpu.reg = (Atmega324CPURegister_TypeDef*) Atmega324CPURegister_Address;
	// EEPROM
	ret.eeprom.reg = (Atmega324Eeprom_TypeDef*) Atmega324Eeprom_Address;
	#if defined(_ATMEGAEEPROM_H_)
		ret.eeprom.enable = EEPROMenable;
	#endif
	// EXINT
	ret.exint.reg = (Atmega324ExternalInterrupts_TypeDef*) Atmega324ExternalInterrupts_Address;
	#if defined(_ATMEGA324INTERRUPT_H_)
		ret.exint.enable = INTERRUPTenable;
	#endif
	// PORT
	ret.porta = (_GPIOA_TypeDef*) Atmega324_GPIOA;
	ret.portb = (_GPIOB_TypeDef*) Atmega324_GPIOB;
	ret.portc = (_GPIOC_TypeDef*) Atmega324_GPIOC;
	ret.portd = (_GPIOD_TypeDef*) Atmega324_GPIOD;
	// JTAG
	ret.jtag.reg = (Atmega324JtagInterface_TypeDef*) Atmega324JtagInterface_Address;
	// SPI
	ret.spi.reg = (Atmega324SerialPeripherialInterface_TypeDef*) Atmega324SerialPeripherialInterface_Address;
	#if defined(_ATMEGA324SPI_H_)
		ret.spi.enable = SPIenable;
	#endif
	// TC1
	ret.tc1.reg = (Atmega324TimerCounter1_TypeDef*) Atmega324TimerCounter1_Address;
	#if defined(_ATMEGA324TIMER_H_)
		ret.tc1.enable = TIMER_COUNTER1enable;
	#endif
	// TC0
	ret.tc0.reg = (Atmega324TimerCounter0_TypeDef*) Atmega324TimerCounter0_Address;
	#if defined(_ATMEGA324TIMER_H_)
		ret.tc0.enable = TIMER_COUNTER0enable;
	#endif
	// TC2
	ret.tc2.reg = (Atmega324TimerCounter2_TypeDef*) Atmega324TimerCounter2_Address;
	#if defined(_ATMEGA324TIMER_H_)
		ret.tc2.enable = TIMER_COUNTER2enable;
	#endif
	// TWI
	ret.twi.reg = (Atmega324TwoWireSerialInterface_TypeDef*) Atmega324TwoWireSerialInterface_Address;
	#if defined(_ATMEGA324TWI_H_)
		ret.twi.enable = TWIenable;
	#endif
	// USART0
	ret.usart0.reg = (Atmega324Usart0_TypeDef*) Atmega324Usart0_Address;
	#if defined(_ATMEGA324UART_H_)
		ret.usart0.enable = UART0enable;
	#endif
	// USART1
	ret.usart1.reg = (Atmega324Usart1_TypeDef*) Atmega324Usart1_Address;
	#if defined(_ATMEGA324UART_H_)
		ret.usart1.enable = UART1enable;
	#endif
	// WDT
	ret.wdt.reg = (Atmega324WatchdogTimer_TypeDef*) Atmega324WatchdogTimer_Address;
	// FUNCS
	ret.readhlbyte = ReadHLByte;
	ret.readlhbyte = ReadLHByte;
	ret.writehlbyte = WriteHLByte;
	ret.writelhbyte = WriteLHByte;
	ret.swapbyte = SwapByte;
	return ret;
}

// COMMON
uint16_t ReadHLByte(_uint16_t reg)
{
	return (reg.par.h.var << 8) | reg.par.l.var;
}
uint16_t ReadLHByte(_uint16_t reg)
{
	return (reg.par.l.var << 8) | reg.par.h.var;
}
_uint16_t WriteHLByte(uint16_t val)
{
	_uint16_t reg; reg.par.h.var = (val >> 8); reg.par.l.var = val;
	return reg;
}
_uint16_t WriteLHByte(uint16_t val)
{
	_uint16_t reg; reg.par.l.var = (val >> 8); reg.par.h.var = val;
	return reg;
}
uint16_t SwapByte(uint16_t num)
{
	uint16_t tp;
	tp = (num << 8);
	return (num >> 8) | tp;
}

/*** File Interrupt ***/
// ISR(RESET_vect){}
// ISR(EXT_INT0_vect){}
// ISR(EXT_INT1_vect){}
// ISR(EXT_INT2_vect){}
// ISR(EXT_INT3_vect){}
// ISR(EXT_INT4_vect){}
// ISR(EXT_INT5_vect){}
// ISR(EXT_INT6_vect){}
// ISR(EXT_INT7_vect){}
// ISR(TIM2_COMP_vect){}
// ISR(TIM2_OVF_vect){}
// ISR(TIM1_CAPT_vect){}
// ISR(TIM1_COMPA_vect){}
// ISR(TIM1_COMPB_vect){}
// ISR(TIM1_OVF_vect){}
// ISR(TIM0_COMP_vect){}
// ISR(TIM0_OVF_vect){}
// ISR(SPI_STC_vect){}
// ISR(USART0_RXC_vect){}
// ISR(USART0_DRE_vect){}
// ISR(USART0_TXC_vect){}
// ISR(ADC_vect){}
// ISR(EE_RDY_vect){}
// ISR(ANA_COMP_vect){}
// ISR(TIM1_COMPC_vect){}
// ISR(USART1_RXC_vect){}
// ISR(USART1_DRE_vect){}
// ISR(USART1_TXC_vect){}
// ISR(TWI_vect){}
// ISR(SPM_RDY_vect){}

/***EOF***/

