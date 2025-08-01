/*************************************************************************
	MM74C923
Author:   <sergio.salazar.santos@gmail.com> 
License:  GNU General Public License
Hardware: 74C923
Date:
*************************************************************************/
/*** Library ***/
#include "mm74c923.h"
#include "explode.h"
#include "function.h"

/*** Constant & Macro ***/
#define MM74C923_KEY_BUFFER_SIZE 16

/*** Variable ***/
static EXPLODE vari;

volatile uint8_t *mm74c923_DDR;
volatile uint8_t *mm74c923_PIN;
volatile uint8_t *mm74c923_PORT;
static uint8_t mm74c923_tmp;
static uint8_t mm74c923_mem;
static uint8_t MM74C923_KEY_CODE_INDEX;
static const char MM74C923_KEY_CODE[]={
	'A', 'B', 'C', 'E', 'G', 'H', 'I', 'J', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V', 'X', 'Y', 'Z',
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 'L', '-', '+', 'F', '7', '8', '9', '#',
	'4', '5', '6', 'U', '1', '2', '3', 'D', '0', '/', '.', '*', '\0'
};
uint8_t MM74C923_KEY_BUFFER_INDEX;
char MM74C923_KEY_BUFFER[MM74C923_KEY_BUFFER_SIZE + 1];
char MM74C923_KEY_BUFFER_EMPTY[] = "";
char* MM74C923_pointer;

/*** Procedure & Function declaration ***/
void MM74C923_activate(void);
char MM74C923_getch(void);
char* MM74C923_gets(void);
char* MM74C923_data(void);
void MM74C923_data_clear(void);

/*** Handler ***/
MM74C923 mm74c923_enable(volatile uint8_t *ddr, volatile uint8_t *pin, volatile uint8_t *port)
{
	// LOCAL VARIABLES
	// ALLOCACAO MEMORIA Para Estrutura
	func_enable();
	vari = explode_enable();
	MM74C923 mm74c923_setup;
	// import parameters
	mm74c923_DDR = ddr;
	mm74c923_PIN = pin;
	mm74c923_PORT = port;
	// initialize variables
	*mm74c923_DDR = (1 << MM74C923_OUTPUT_ENABLE);
	*mm74c923_PORT = 0xFF;
	mm74c923_tmp &= ~(1 << MM74C923_DATA_AVAILABLE);
	mm74c923_mem &= ~(1 << MM74C923_DATA_AVAILABLE);
	MM74C923_pointer = MM74C923_KEY_BUFFER_EMPTY;
	// Direccionar apontadores para PROTOTIPOS
	mm74c923_setup.activate = MM74C923_activate;
	mm74c923_setup.getch = MM74C923_getch;
	mm74c923_setup.gets = MM74C923_gets;
	mm74c923_setup.data = MM74C923_data;
	mm74c923_setup.data_clear = MM74C923_data_clear;
	
	return mm74c923_setup;
}

/*** Procedure & Function definition ***/
void MM74C923_activate(void){
	vari.update(&vari.par, *mm74c923_PIN);
}
char MM74C923_getch(void)
{
	uint8_t c, lh;
	// uint8_t hl;
	lh = vari.par.LH; // low to high bit mask
	// hl=vari.HL(mm74c923_mem, mm74c923_tmp); // high to low bit mask
	if(lh & (1 << MM74C923_DATA_AVAILABLE)){
		*mm74c923_PORT &= ~(1 << MM74C923_OUTPUT_ENABLE);
		c = *mm74c923_PIN;
		if(c & 1 << MM74C923_DATA_OUT_A) MM74C923_KEY_CODE_INDEX |= 1; else MM74C923_KEY_CODE_INDEX &= ~1;
		if(c & 1 << MM74C923_DATA_OUT_B) MM74C923_KEY_CODE_INDEX |= 2; else MM74C923_KEY_CODE_INDEX &= ~2;
		if(c & 1 << MM74C923_DATA_OUT_C) MM74C923_KEY_CODE_INDEX |= 4; else MM74C923_KEY_CODE_INDEX &= ~4;
		if(c & 1 << MM74C923_DATA_OUT_D) MM74C923_KEY_CODE_INDEX |= 8; else MM74C923_KEY_CODE_INDEX &= ~8;
		if(c & 1 << MM74C923_DATA_OUT_E) MM74C923_KEY_CODE_INDEX |= 16; else MM74C923_KEY_CODE_INDEX &= ~16;
		if(c & 1 << MM74C923_EXTRA_DATA_OUT_PIN) MM74C923_KEY_CODE_INDEX |= 32; else MM74C923_KEY_CODE_INDEX &= ~32;
	// }else if(hl & (1 << MM74C923_DATA_AVAILABLE)){
		*mm74c923_PORT |= (1<<MM74C923_OUTPUT_ENABLE);
		// MM74C923_KEY_CODE_INDEX = 52;
	}else
		MM74C923_KEY_CODE_INDEX = 52;
	return MM74C923_KEY_CODE[MM74C923_KEY_CODE_INDEX];
}
char* MM74C923_gets(void)
{
	char c;
	c = MM74C923_getch();
	if(c == '*'){ // used has enter key
		MM74C923_KEY_BUFFER_INDEX=0;
	}else if(c != '\0'){
		if(MM74C923_KEY_BUFFER_INDEX<MM74C923_KEY_BUFFER_SIZE - 1){ // BUFFER FULL IGNORE DATA
			MM74C923_KEY_BUFFER[MM74C923_KEY_BUFFER_INDEX] = c;
			MM74C923_KEY_BUFFER_INDEX++;
			MM74C923_KEY_BUFFER[MM74C923_KEY_BUFFER_INDEX] = '\0';
		}
	}
	return MM74C923_KEY_BUFFER;
}
char* MM74C923_data(void){
	if(MM74C923_KEY_BUFFER_INDEX)
		MM74C923_pointer = MM74C923_KEY_BUFFER_EMPTY;
	else
		MM74C923_pointer = MM74C923_KEY_BUFFER;
	return MM74C923_pointer;
}
void MM74C923_data_clear(void){
	MM74C923_KEY_BUFFER_INDEX = 0;
	MM74C923_KEY_BUFFER[MM74C923_KEY_BUFFER_INDEX] = '\0';
}

/*** EOF ***/

