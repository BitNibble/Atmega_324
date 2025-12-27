/************************************************************************
	ATMEGA 324
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date:     04/07/2025
************************************************************************/
#include "atmega324.h"

/*****************************/
/**** MAIN HARDWARE LAYER ****/
/*****************************/
// Indirect Address Register
static const GPIAR_TypeDef gpiar = {
	.X = ((U_word*) 0x001A), 
	.Y = ((U_word*) 0x001C), 
	.Z = ((U_word*) 0x001E) 
};
// Singleton accessor
GPIAR_TypeDef* gpiar_reg(void) { return (GPIAR_TypeDef*) &gpiar; }
// Static instance with mapped register addresses
static const GPIOA_TypeDef gpioa = {
	.pin = ((U_byte*) 0x0020), 
	.ddr = ((U_byte*) 0x0021), 
	.port = ((U_byte*) 0x0022) 
};
GPIOA_TypeDef* gpioa_reg(void) { return (GPIOA_TypeDef*) &gpioa; }
// Static instance with mapped register addresses
static const GPIOB_TypeDef gpiob = {
	.pin = ((U_byte*) 0x0023),
	.ddr = ((U_byte*) 0x0024), 
	.port = ((U_byte*) 0x0025) 
};
GPIOB_TypeDef* gpiob_reg(void) { return (GPIOB_TypeDef*) &gpiob; }
// Static instance with mapped register addresses
static const GPIOC_TypeDef gpioc = {
	.pin = ((U_byte*) 0x0026), 
	.ddr = ((U_byte*) 0x0027), 
	.port = ((U_byte*) 0x0028) 
};
GPIOC_TypeDef* gpioc_reg(void) { return (GPIOC_TypeDef*) &gpioc; }
// Static instance with mapped register addresses
static const GPIOD_TypeDef gpiod = {
	.pin = ((U_byte*) 0x0029), 
	.ddr = ((U_byte*) 0x002A), 
	.port = ((U_byte*) 0x002B) 
};
GPIOD_TypeDef* gpiod_reg(void) { return (GPIOD_TypeDef*) &gpiod; }
// Static instance with mapped register addresses
static const Atmega324ExternalInterrupts_TypeDef exint = {
	.pcifr = (PCIFR_TypeDef*) 0x003B,
	.eifr = (EIFR_TypeDef*) 0x003C,
	.eimsk = (EIMSK_TypeDef*) 0x003D,
	.pcicr = (PCICR_TypeDef*) 0x0068,
	.eicra = (EICRA_TypeDef*) 0x0069,
	.pcmsk0 = (PCMSK0_TypeDef*) 0x006B,
	.pcmsk1 = (PCMSK1_TypeDef*) 0x006C,
	.pcmsk2 = (PCMSK2_TypeDef*) 0x006D,
	.pcmsk3 = (PCMSK3_TypeDef*) 0x0073
};
Atmega324ExternalInterrupts_TypeDef* exint_reg(void) {
	return (Atmega324ExternalInterrupts_TypeDef*) &exint;
}
// Static instance with hardware register mappings
static const Atmega324AnalogComparator_TypeDef ac = {
	.acsr = (ACSR_TypeDef*) 0x0050,
	.adcsrb = (ADCSRB_TypeDef*) 0x007B,
	.didr1 = (DIDR1_TypeDef*) 0x007F
};
Atmega324AnalogComparator_TypeDef* ac_reg(void) {
	return (Atmega324AnalogComparator_TypeDef*) &ac;
}
// Static instance with hardware bindings
static const Atmega324AnalogToDigitalConverter_TypeDef adc = {
	.adc = (U_word*) 0x0078,
	.adcsra = (ADCSRA_TypeDef*) 0x007A,
	.adcsrb = (ADCSRB_TypeDef*) 0x007B,
	.admux = (ADMUX_TypeDef*) 0x007C,
	.didr0 = (DIDR0_TypeDef*) 0x007E
};
Atmega324AnalogToDigitalConverter_TypeDef* adc_reg(void) {
	return (Atmega324AnalogToDigitalConverter_TypeDef*) &adc;
}
// Static instance with hardware mapping
static const Atmega324BootLoader_TypeDef boot = {
	.spmcsr = (SPMCSR_TypeDef*) 0x0057
};
Atmega324BootLoader_TypeDef* boot_reg(void) {
	return (Atmega324BootLoader_TypeDef*) &boot;
}
// Static instance
static const Atmega324CPURegister_TypeDef cpu = {
	.gpior0 = (U_byte*) 0x003E,
	.gpior1 = (U_byte*) 0x004A,
	.gpior2 = (U_byte*) 0x004B,
	.smcr = (SMCR_TypeDef*) 0x0053,
	.mcusr = (MCUSR_TypeDef*) 0x0054,
	.mcucr = (MCUCR_TypeDef*) 0x0055,
	.sp = (U_word*) 0x005D,
	.sreg = (SREG_TypeDef*) 0x005F,
	.clkpr = (CLKPR_TypeDef*) 0x0061,
	.prr0 = (PRR_TypeDef*) 0x0064,
	.osccal = (U_byte*) 0x0066
};
Atmega324CPURegister_TypeDef* cpu_reg(void) {
	return (Atmega324CPURegister_TypeDef*) &cpu;
}
// Static instance
static const Atmega324Eeprom_TypeDef eeprom = {
	.eecr = (EECR_TypeDef*) 0x003F,
	.eedr = (U_byte*) 0x0040,
	.eear = (U_word*) 0x0041
};
Atmega324Eeprom_TypeDef* eeprom_reg(void) {
	return (Atmega324Eeprom_TypeDef*) &eeprom;
}
// Static instance
static const Atmega324JtagInterface_TypeDef jtag = {
	.ocdr = (U_byte*) 0x0051,
	.mcusr = (MCUSR_TypeDef*) 0x0054,
	.mcucr = (MCUCR_TypeDef*) 0x0055
};
Atmega324JtagInterface_TypeDef* jtag_reg(void) {
	return (Atmega324JtagInterface_TypeDef*) &jtag;
}
// Static instance
static const Atmega324SerialPeripherialInterface_TypeDef spi = {
	.spcr0 = (SPCR_TypeDef*) 0x004C,
	.spsr0 = (SPSR_TypeDef*) 0x004D,
	.spdr0 = (U_byte*) 0x004E
};
Atmega324SerialPeripherialInterface_TypeDef* spi_reg(void) {
	return (Atmega324SerialPeripherialInterface_TypeDef*) &spi;
}
// Static instance
static const Atmega324TimerCounter1_TypeDef tc1 = {
	.tifr1 = (TIFR1_TypeDef*) 0x0036,
	.timsk1 = (TIMSK1_TypeDef*) 0x006F,
	.tccr1a = (TCCR1A_TypeDef*) 0x0080,
	.tccr1b = (TCCR1B_TypeDef*) 0x0081,
	.tccr1c = (TCCR1C_TypeDef*) 0x0082,
	.tcnt1 = (U_word*) 0x0084,
	.icr1 = (U_word*) 0x0086,
	.ocr1a = (U_word*) 0x0088,
	.ocr1b = (U_word*) 0x008A
};
Atmega324TimerCounter1_TypeDef* tc1_reg(void) {
	return (Atmega324TimerCounter1_TypeDef*) &tc1;
}
// Static instance
static const Atmega324TimerCounter3_TypeDef tc3 = {
	.tifr3 = (TIFR3_TypeDef*) 0x0038,
	.timsk3 = (TIMSK3_TypeDef*) 0x0071,
	.tccr3a = (TCCR3A_TypeDef*) 0x0090,
	.tccr3b = (TCCR3B_TypeDef*) 0x0091,
	.tccr3c = (TCCR3C_TypeDef*) 0x0092,
	.tcnt3 = (U_word*) 0x0094,
	.icr3 = (U_word*) 0x0096,
	.ocr3a = (U_word*) 0x0098,
	.ocr3b = (U_word*) 0x009A
};
Atmega324TimerCounter3_TypeDef* tc3_reg(void) {
	return (Atmega324TimerCounter3_TypeDef*) &tc3;
}
// Static instance
static const Atmega324TimerCounter0_TypeDef tc0 = {
	.tifr0 = (TIFR0_TypeDef*) 0x0035,
	.gtccr = (GTCCR_TypeDef*) 0x0043,
	.tccr0a = (TCCR0A_TypeDef*) 0x0044,
	.tccr0b = (TCCR0B_TypeDef*) 0x0045,
	.tcnt0 = (U_byte*) 0x0046,
	.ocr0a = (U_byte*) 0x0047,
	.ocr0b = (U_byte*) 0x0048,
	.timsk0 = (TIMSK0_TypeDef*) 0x006E
};
Atmega324TimerCounter0_TypeDef* tc0_reg(void) {
	return (Atmega324TimerCounter0_TypeDef*) &tc0;
}
// Static instance
static const Atmega324TimerCounter2_TypeDef tc2 = {
	.tifr2 = (TIFR2_TypeDef*) 0x0037,
	.gtccr = (GTCCR_TypeDef*) 0x0043,
	.timsk2 = (TIMSK2_TypeDef*) 0x0070,
	.tccr2a = (TCCR2A_TypeDef*) 0x00B0,
	.tccr2b = (TCCR2B_TypeDef*) 0x00B1,
	.tcnt2 = (U_byte*) 0x00B2,
	.ocr2a = (U_byte*) 0x00B3,
	.ocr2b = (U_byte*) 0x00B4,
	.assr = (ASSR_TypeDef*) 0x00B6
};
Atmega324TimerCounter2_TypeDef* tc2_reg(void) {
	return (Atmega324TimerCounter2_TypeDef*) &tc2;
}
// Static instance
static const Atmega324TwoWireSerialInterface_TypeDef twi = {
	.twbr = (U_byte*) 0x00B8,
	.twsr = (TWSR_TypeDef*) 0x00B9,
	.twar = (TWAR_TypeDef*) 0x00BA,
	.twdr = (U_byte*) 0x00BB,
	.twcr = (TWCR_TypeDef*) 0x00BC,
	.twamr = (TWAMR_TypeDef*) 0x00BD
};
Atmega324TwoWireSerialInterface_TypeDef* twi_reg(void) {
	return (Atmega324TwoWireSerialInterface_TypeDef*) &twi;
}
// Static instance
static const Atmega324Usart0_TypeDef usart0 = {
	.ucsr0a = (UCSR0A_TypeDef*) 0x00C0,
	.ucsr0b = (UCSR0B_TypeDef*) 0x00C1,
	.ucsr0c = (UCSR0C_TypeDef*) 0x00C2,
	.ubrr0 = (U_word*) 0x00C4,
	.udr0 = (U_byte*) 0x00C6
};
Atmega324Usart0_TypeDef* usart0_reg(void) {
	return (Atmega324Usart0_TypeDef*) &usart0;
}
// Static instance with register mappings
static const Atmega324Usart1_TypeDef usart1 = {
	.ucsr1a = (UCSR1A_TypeDef*) 0x00C8,
	.ucsr1b = (UCSR1B_TypeDef*) 0x00C9,
	.ucsr1c = (UCSR1C_TypeDef*) 0x00CA,
	.ubrr1 = (U_word*) 0x00CC,
	.udr1 = (U_byte*) 0x00CE
};
Atmega324Usart1_TypeDef* usart1_reg(void) {
	return (Atmega324Usart1_TypeDef*) &usart1;
}
// Static instance with register mappings
static const Atmega324WatchdogTimer_TypeDef wdt = {
	.wdtcsr = (WDTCSR_TypeDef*) 0x0060
};
Atmega324WatchdogTimer_TypeDef* wdt_reg(void) {
	return (Atmega324WatchdogTimer_TypeDef*) &wdt;
}

/*******************************************************************/
/********************** MAIN HARDWARE LAYER ************************/
/*******************************************************************/
static const dev_atmega324 atmega324_setup = {
	.gpiar = (GPIAR_TypeDef*) &gpiar,
	.ac = (Atmega324AnalogComparator_TypeDef*) &ac,
	.adc = (Atmega324AnalogToDigitalConverter_TypeDef*) &adc,
	.bootload = (Atmega324BootLoader_TypeDef*) &boot,
	.cpu = (Atmega324CPURegister_TypeDef*) &cpu,
	.eeprom = (Atmega324Eeprom_TypeDef*) &eeprom,
	.exint = (Atmega324ExternalInterrupts_TypeDef*) &exint,
	.gpioa = (GPIOA_TypeDef*) &gpioa,
	.gpiob = (GPIOB_TypeDef*) &gpiob,
	.gpioc = (GPIOC_TypeDef*) &gpioc,
	.gpiod = (GPIOD_TypeDef*) &gpiod,
	.jtag = (Atmega324JtagInterface_TypeDef*) &jtag,
	.spi = (Atmega324SerialPeripherialInterface_TypeDef*) &spi,
	.tc1 = (Atmega324TimerCounter1_TypeDef*) &tc1,
	.tc3 = (Atmega324TimerCounter3_TypeDef*) &tc3,
	.tc2 = (Atmega324TimerCounter2_TypeDef*) &tc2,
	.tc0 = (Atmega324TimerCounter0_TypeDef*) &tc0,
	.twi = (Atmega324TwoWireSerialInterface_TypeDef*) &twi,
	.usart0 = (Atmega324Usart0_TypeDef*) &usart0,
	.usart1 = (Atmega324Usart1_TypeDef*) &usart1,
	.wdt = (Atmega324WatchdogTimer_TypeDef*) &wdt
};
// Singleton accessor
dev_atmega324* dev(void){ return (dev_atmega324*) &atmega324_setup; }

/*********************************************************************/
/**************** Procedure and Function definition ******************/
/*********************************************************************/
uint16_t readHLbyte(U_word reg){
	return (reg.par.h.var << 8) | reg.par.l.var;
}
uint16_t readLHbyte(U_word reg){
	return (reg.par.l.var << 8) | reg.par.h.var;
}
U_word writeHLbyte(uint16_t val){
	U_word reg; reg.par.h.var = (val >> 8) & 0xFF; reg.par.l.var = val & 0xFF; return reg;
}
U_word writeLHbyte(uint16_t val){
	U_word reg; reg.par.l.var = (val >> 8) & 0xFF; reg.par.h.var = val & 0xFF; return reg;
}
uint16_t SwapByte(uint16_t num){uint16_t tp; tp = (num << 8); return (num >> 8) | tp;}

/*********************************************************************/
/**************** Procedure and Function definition ******************/
/*********************************************************************/
uint16_t BAUDRATEnormal(uint32_t BAUD){uint32_t baudrate = F_CPU/16; baudrate /= BAUD; baudrate -= 1; return (uint16_t) baudrate;}
uint16_t BAUDRATEdouble(uint32_t BAUD){uint32_t baudrate = F_CPU/8; baudrate /= BAUD; baudrate -= 1; return (uint16_t) baudrate;}
uint16_t BAUDRATEsynchronous(uint32_t BAUD){uint32_t baudrate = F_CPU/2; baudrate /= BAUD; baudrate -= 1; return (uint16_t) baudrate;}

/*********************************************************************/
/**************** Procedure and Function definition ******************/
/*********************************************************************/
inline uint8_t Msk_Pos(uint8_t Msk){
	uint8_t Pos = 0;
	if( Msk ){
		for( ; !(Msk & 1); Msk >>= 1, Pos++ );
	}
	return Pos;
}
/*** SUB Tools ***/
inline uint8_t _get_pos(uint8_t size_block, uint8_t block_n){
	return size_block * block_n;
}
inline uint8_t _var_mask(uint8_t var, uint8_t Msk){
	return (var & Msk);
}
inline uint8_t _var_imask(uint8_t var, uint8_t Msk){
	return (var & ~Msk);
}
inline uint8_t _size_to_block(uint8_t size_block){
	return (size_block >= BYTE_BITS) ? 0xFFU : ((1U << size_block) - 1);
}
inline uint8_t _block_to_size(uint8_t block) {
	return block ? ((unsigned int)BYTE_BITS - __builtin_clz(block)) : 0U;
}
inline uint8_t _get_mask(uint8_t size_block, uint8_t Pos){
	return _size_to_block(size_block) << Pos;
}
inline uint8_t _mask_pos(uint8_t Msk){
	return Msk ? (unsigned int)__builtin_ctz(Msk) : 0U;
}
inline uint8_t _mask_data(uint8_t Msk, uint8_t data){
	return _var_mask(data << _mask_pos(Msk), Msk);
}
// --- Generic helpers ---
inline uint8_t reg_get(uint8_t reg, uint8_t Msk){
	return _var_mask(reg, Msk) >> _mask_pos(Msk);
}

inline void reg_set(volatile uint8_t *reg, uint8_t Msk, uint8_t data){
	*reg = _var_imask(*reg, Msk) | _mask_data(Msk, data);
}
/*** Tools ***/
void set_reg(volatile uint8_t* reg, uint8_t hbits){
	*reg |= hbits;
}
void clear_reg(volatile uint8_t* reg, uint8_t hbits){
	*reg &= ~hbits;
}
inline uint8_t get_reg_Msk_Pos(uint8_t reg, uint8_t Msk, uint8_t Pos)
{
	return _var_mask(reg, Msk) >> Pos;
}
inline void write_reg_Msk_Pos(volatile uint8_t* reg, uint8_t Msk, uint8_t Pos, uint8_t data)
{
	uint8_t value = _var_imask(*reg, Msk);
	data = _var_mask((data << Pos), Msk); value |= data; *reg = value;
}
inline void set_reg_Msk_Pos(volatile uint8_t* reg, uint8_t Msk, uint8_t Pos, uint8_t data)
{
	data = _var_mask((data << Pos), Msk); clear_reg(reg, Msk); set_reg(reg, data);
}
uint8_t get_reg_Msk(uint8_t reg, uint8_t Msk)
{
	return get_reg_Msk_Pos(reg, Msk, _mask_pos(Msk));
}
void write_reg_Msk(volatile uint8_t* reg, uint8_t Msk, uint8_t data)
{
	write_reg_Msk_Pos(reg, Msk, _mask_pos(Msk), data);
}
void set_reg_Msk(volatile uint8_t* reg, uint8_t Msk, uint8_t data)
{
	set_reg_Msk_Pos(reg, Msk, _mask_pos(Msk), data);
}
uint8_t get_reg_block(uint8_t reg, uint8_t size_block, uint8_t Pos)
{
	return get_reg_Msk_Pos(reg, _get_mask(size_block, Pos), Pos);
}
void write_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t Pos, uint8_t data)
{
	write_reg_Msk_Pos(reg, _get_mask(size_block, Pos), Pos, data);
}
void set_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t Pos, uint8_t data)
{
	set_reg_Msk_Pos(reg, _get_mask(size_block, Pos), Pos, data);
}
uint8_t get_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t Pos)
{
	uint16_t n = Pos / BYTE_BITS; Pos = Pos % BYTE_BITS;
	return get_reg_Msk_Pos((uint8_t)*(reg + n), _get_mask(size_block, Pos), Pos);
}
void set_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t Pos, uint8_t data)
{
	uint16_t n = Pos / BYTE_BITS; Pos = Pos % BYTE_BITS;
	set_reg_Msk_Pos((reg + n), _get_mask(size_block, Pos), Pos, data);
}

/*********************************************************************/
/**************** Procedure and Function definition ******************/
/*********************************************************************/
int isPtrNull(void* ptr) {
	return ptr ? 0 : 1; // Returns 1 if NULL, 0 otherwise
}
int isCharPtrFlush(void* ptr) {
	if (ptr == NULL) return 1;
	// Cast the void pointer to a char pointer to dereference it
	return *((unsigned char*)ptr) ? 0 : 1; // Returns 1 if '\0', 0 otherwise
}

/*** EOF ***/

