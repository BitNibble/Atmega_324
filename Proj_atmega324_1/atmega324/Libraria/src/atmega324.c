/************************************************************************
	ATMEGA 324
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date:     28/06/2025
************************************************************************/
#include "atmega324.h"

static const _GPIOA_TypeDef gpioa  = {.pin = ((_uint8_t*) 0x0020), .ddr = ((_uint8_t*) 0x0021), .port = ((_uint8_t*) 0x0022) };
_GPIOA_TypeDef* gpioa_reg(void) {  return (_GPIOA_TypeDef*) &gpioa; }
	
static const _GPIOB_TypeDef gpiob  = {.pin = ((_uint8_t*) 0x0023), .ddr = ((_uint8_t*) 0x0024), .port = ((_uint8_t*) 0x0025) };
_GPIOB_TypeDef* gpiob_reg(void) {  return (_GPIOB_TypeDef*) &gpiob; }
	
static const _GPIOC_TypeDef gpioc  = {.pin = ((_uint8_t*) 0x0026), .ddr = ((_uint8_t*) 0x0027), .port = ((_uint8_t*) 0x0028) };
_GPIOC_TypeDef* gpioc_reg(void) {  return (_GPIOC_TypeDef*) &gpioc; }
	
static const _GPIOD_TypeDef gpiod  = {.pin = ((_uint8_t*) 0x0029), .ddr = ((_uint8_t*) 0x002A), .port = ((_uint8_t*) 0x002B) };
_GPIOD_TypeDef* gpiod_reg(void) {  return (_GPIOD_TypeDef*) &gpiod; }

// Static instance with mapped register addresses
static const Atmega324ExternalInterrupts_TypeDef exint = {
	.pcifr   = (_PCIFR_TypeDef*)   0x003B,
	.eifr    = (_EIFR_TypeDef*)    0x003C,
	.eimsk   = (_EIMSK_TypeDef*)   0x003D,
	.pcicr   = (_PCICR_TypeDef*)   0x0068,
	.eicra   = (_EICRA_TypeDef*)   0x0069,
	.pcmsk0  = (_PCMSK0_TypeDef*)  0x006B,
	.pcmsk1  = (_PCMSK1_TypeDef*)  0x006C,
	.pcmsk2  = (_PCMSK2_TypeDef*)  0x006D,
	.pcmsk3  = (_PCMSK3_TypeDef*)  0x0073
};
// Singleton-style accessor
Atmega324ExternalInterrupts_TypeDef* exint_reg(void) {
	return (Atmega324ExternalInterrupts_TypeDef*) &exint;
}
// Static instance with hardware register mappings
static const Atmega324AnalogComparator_TypeDef ac = {
	.acsr   = (_ACSR_TypeDef*)  0x0050,
	.adcsrb = (_ADCSRB_TypeDef*) 0x007B,
	.didr1  = (_DIDR1_TypeDef*) 0x007F
};
// Singleton accessor
Atmega324AnalogComparator_TypeDef* ac_reg(void) {
	return (Atmega324AnalogComparator_TypeDef*) &ac;
}
// Static instance with hardware bindings
static const Atmega324AnalogToDigitalConverter_TypeDef adc = {
	.adc     = (_uint16_t*) 0x0078,      // ADC Data register
	.adcsra  = (_ADCSRA_TypeDef*) 0x007A,
	.adcsrb  = (_ADCSRB_TypeDef*) 0x007B,
	.admux   = (_ADMUX_TypeDef*)  0x007C,
	.didr0   = (_DIDR0_TypeDef*)  0x007E
};
// Singleton accessor
Atmega324AnalogToDigitalConverter_TypeDef* adc_reg(void) {
	return (Atmega324AnalogToDigitalConverter_TypeDef*) &adc;
}
// Static instance with hardware mapping
static const Atmega324BootLoader_TypeDef boot = {
	.spmcsr = (_SPMCSR_TypeDef*) 0x0057
};
// Singleton accessor
Atmega324BootLoader_TypeDef* boot_reg(void) {
	return (Atmega324BootLoader_TypeDef*) &boot;
}
// Static instance
static const Atmega324CPURegister_TypeDef cpu = {
	.gpior0 = (_uint8_t*)     0x003E,
	.gpior1 = (_uint8_t*)     0x004A,
	.gpior2 = (_uint8_t*)     0x004B,
	.smcr   = (_SMCR_TypeDef*)   0x0053,
	.mcusr  = (_MCUSR_TypeDef*)  0x0054,
	.mcucr  = (_MCUCR_TypeDef*)  0x0055,
	.sp     = (_uint16_t*)    0x005D,  // Stack Pointer (SPH: 0x5D, SPL: 0x5E)
	.sreg   = (_SREG_TypeDef*)   0x005F,
	.clkpr  = (_CLKPR_TypeDef*)  0x0061,
	.prr0   = (_PRR_TypeDef*)    0x0064,
	.osccal = (_uint8_t*)     0x0066
};
// Singleton accessor
Atmega324CPURegister_TypeDef* cpu_reg(void) {
	return (Atmega324CPURegister_TypeDef*) &cpu;
}
// Static instance
static const Atmega324Eeprom_TypeDef eeprom = {
	.eecr = (_EECR_TypeDef*)  0x003F,
	.eedr = (_uint8_t*)       0x0040,
	.eear = (_uint16_t*)      0x0041
};
// Singleton accessor
Atmega324Eeprom_TypeDef* eeprom_reg(void) {
	return (Atmega324Eeprom_TypeDef*) &eeprom;
}
// Static instance
static const Atmega324JtagInterface_TypeDef jtag = {
	.ocdr  = (_uint8_t*)       0x0051,
	.mcusr = (_MCUSR_TypeDef*) 0x0054,
	.mcucr = (_MCUCR_TypeDef*) 0x0055
};
// Singleton accessor
Atmega324JtagInterface_TypeDef* jtag_reg(void) {
	return (Atmega324JtagInterface_TypeDef*) &jtag;
}
// Static instance
static const Atmega324SerialPeripherialInterface_TypeDef spi = {
	.spcr0 = (_SPCR_TypeDef*) 0x004C,
	.spsr0 = (_SPSR_TypeDef*) 0x004D,
	.spdr0 = (_uint8_t*)      0x004E
};
// Singleton accessor
Atmega324SerialPeripherialInterface_TypeDef* spi_reg(void) {
	return (Atmega324SerialPeripherialInterface_TypeDef*) &spi;
}
// Static instance
static const Atmega324TimerCounter1_TypeDef tc1 = {
	.tifr1   = (_TIFR1_Typedef*)  0x0036,
	.timsk1  = (_TIMSK1_TypeDef*) 0x006F,
	.tccr1a  = (_TCCR1A_TypeDef*) 0x0080,
	.tccr1b  = (_TCCR1B_TypeDef*) 0x0081,
	.tccr1c  = (_TCCR1C_TypeDef*) 0x0082,
	.tcnt1   = (_uint16_t*)       0x0084,
	.icr1    = (_uint16_t*)       0x0086,
	.ocr1a   = (_uint16_t*)       0x0088,
	.ocr1b   = (_uint16_t*)       0x008A
};
// Singleton accessor
Atmega324TimerCounter1_TypeDef* tc1_reg(void) {
	return (Atmega324TimerCounter1_TypeDef*) &tc1;
}
// Static instance
static const Atmega324TimerCounter0_TypeDef tc0 = {
	.tifr0  = (_TIFR0_Typedef*)  0x0035,
	.gtccr  = (_GTCCR_TypeDef*)  0x0043,
	.tccr0a = (_TCCR0A_TypeDef*) 0x0044,
	.tccr0b = (_TCCR0B_TypeDef*) 0x0045,
	.tcnt0  = (_uint8_t*)        0x0046,
	.ocr0a  = (_uint8_t*)        0x0047,
	.ocr0b  = (_uint8_t*)        0x0048,
	.timsk0 = (_TIMSK0_TypeDef*) 0x006E
};
// Singleton accessor
Atmega324TimerCounter0_TypeDef* tc0_reg(void) {
	return (Atmega324TimerCounter0_TypeDef*) &tc0;
}
// Static instance
static const Atmega324TimerCounter2_TypeDef tc2 = {
	.tifr2  = (_TIFR2_Typedef*)  0x0037,
	.gtccr  = (_GTCCR_TypeDef*)  0x0043,
	.timsk2 = (_TIMSK2_TypeDef*) 0x0070,
	.tccr2a = (_TCCR2A_TypeDef*) 0x00B0,
	.tccr2b = (_TCCR2B_TypeDef*) 0x00B1,
	.tcnt2  = (_uint8_t*)        0x00B2,
	.ocr2a  = (_uint8_t*)        0x00B3,
	.ocr2b  = (_uint8_t*)        0x00B4,
	.assr   = (_ASSR_TypeDef*)   0x00B6
};
// Singleton accessor
Atmega324TimerCounter2_TypeDef* tc2_reg(void) {
	return (Atmega324TimerCounter2_TypeDef*) &tc2;
}
// Static instance
static const Atmega324TwoWireSerialInterface_TypeDef twi = {
	.twbr  = (_uint8_t*)        0x00B8,
	.twsr  = (_TWSR_TypeDef*)   0x00B9,
	.twar  = (_TWAR_TypeDef*)   0x00BA,
	.twdr  = (_uint8_t*)        0x00BB,
	.twcr  = (_TWCR_TypeDef*)   0x00BC,
	.twamr = (_TWAMR_TypeDef*)  0x00BD
};
// Singleton accessor
Atmega324TwoWireSerialInterface_TypeDef* twi_reg(void) {
	return (Atmega324TwoWireSerialInterface_TypeDef*) &twi;
}
// Static instance
static const Atmega324Usart0_TypeDef usart0 = {
	.ucsr0a = (_UCSR0A_TypeDef*) 0x00C0,
	.ucsr0b = (_UCSR0B_TypeDef*) 0x00C1,
	.ucsr0c = (_UCSR0C_TypeDef*) 0x00C2,
	.ubrr0  = (_uint16_t*)       0x00C4,
	.udr0   = (_uint8_t*)   0x00C6
};
// Singleton accessor
Atmega324Usart0_TypeDef* usart0_reg(void) {
	return (Atmega324Usart0_TypeDef*) &usart0;
}
// Static instance with register mappings
static const Atmega324Usart1_TypeDef usart1 = {
	.ucsr1a = (_UCSR1A_TypeDef*) 0x00C8,
	.ucsr1b = (_UCSR1B_TypeDef*) 0x00C9,
	.ucsr1c = (_UCSR1C_TypeDef*) 0x00CA,
	.ubrr1  = (_uint16_t*)       0x00CC,  // 16-bit pointer to UBRR1H/L
	.udr1   = (_uint8_t*)        0x00CE
};
// Singleton accessor
Atmega324Usart1_TypeDef* usart1_reg(void) {
	return (Atmega324Usart1_TypeDef*) &usart1;
}
// Static instance with register mappings
static const Atmega324WatchdogTimer_TypeDef wdt = {
	.wdtcsr = (_WDTCSR_TypeDef*) 0x0060
};
// Singleton accessor
Atmega324WatchdogTimer_TypeDef* wdt_reg(void) {
	return (Atmega324WatchdogTimer_TypeDef*) &wdt;
}
/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/
/*** Atmega 128 Procedure and Function ***/
uint16_t SwapByte(uint16_t num){uint16_t tp; tp = (num << 8); return (num >> 8) | tp;}
uint16_t BAUDRATEnormal(uint32_t BAUD){uint32_t baudrate = F_CPU/16; baudrate /= BAUD; baudrate -= 1; return (uint16_t) baudrate;}
uint16_t BAUDRATEdouble(uint32_t BAUD){uint32_t baudrate = F_CPU/8; baudrate /= BAUD; baudrate -= 1; return (uint16_t) baudrate;}
uint16_t BAUDRATEsynchronous(uint32_t BAUD){uint32_t baudrate = F_CPU/2; baudrate /= BAUD; baudrate -= 1; return (uint16_t) baudrate;}

/*** Procedure and Function ToolSet ***/
inline void set_reg(volatile uint8_t* reg, uint8_t hbits){
	*reg |= hbits;
}
inline void clear_reg(volatile uint8_t* reg, uint8_t hbits){
	*reg &= ~hbits;
}
uint8_t get_reg_block(uint8_t reg, uint8_t size_block, uint8_t bit_n)
{
	if(bit_n < BYTE_BITS &&  size_block != 0 && bit_n + size_block <= BYTE_BITS) {
		uint8_t mask = (uint8_t)((1U << size_block) - 1);
		reg = (reg & (mask << bit_n)) >> bit_n;
	}
	return reg;
}
void write_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data)
{
	uint8_t value = *reg;
	if(bit_n < BYTE_BITS &&  size_block != 0 && bit_n + size_block <= BYTE_BITS) {
		uint8_t mask = (uint8_t)((1U << size_block) - 1);
		data &= mask; value &= ~(mask << bit_n);
		data = (data << bit_n);
		value |= data;
		*reg = value;
	}
}
void set_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data)
{
	if(bit_n < BYTE_BITS &&  size_block != 0 && bit_n + size_block <= BYTE_BITS) {
		uint8_t mask = (uint8_t)((1U << size_block) - 1);
		data &= mask;
		*reg &= ~(mask << bit_n);
		*reg |= (data << bit_n);
	}
}
uint8_t get_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n)
{
	uint8_t value;
	uint8_t n = bit_n / BYTE_BITS; bit_n = bit_n % BYTE_BITS;
	value = *(reg + n );
	if(size_block != 0 && bit_n + size_block <= BYTE_BITS){
		uint8_t mask = (uint8_t)((1U << size_block) - 1);
		value = (value & (mask << bit_n)) >> bit_n;
	}
	return value;
}
void set_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data)
{
	uint8_t n = bit_n / BYTE_BITS; bit_n = bit_n % BYTE_BITS;
	if(size_block != 0 && bit_n + size_block <= BYTE_BITS) {
		uint8_t mask = (uint8_t)((1U << size_block) - 1);
		data &= mask;
		*(reg + n ) &= ~(mask << bit_n);
		*(reg + n ) |= (data << bit_n);
	}
}

