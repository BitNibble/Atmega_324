/*** Timer0 Register Typedefs ***/
typedef volatile union {
	struct {
		uint8_t tov0 : 1;
		uint8_t ocf0a : 1;
		uint8_t ocf0b : 1;
		uint8_t : 5;
	} par;
	uint8_t var;
} _TIFR0_TypeDef;  // 0x0035

typedef volatile union {
	struct {
		uint8_t tocie0b : 1;
		uint8_t tocie0a : 1;
		uint8_t toie0 : 1;
		uint8_t : 5;
	} par;
	uint8_t var;
} _TIMSK0_TypeDef;  // 0x006E

typedef volatile union {
	struct {
		uint8_t com0a1 : 1;
		uint8_t com0a0 : 1;
		uint8_t com0b1 : 1;
		uint8_t com0b0 : 1;
		uint8_t wgm01 : 1;
		uint8_t wgm00 : 1;
		uint8_t : 2;
	} par;
	uint8_t var;
} _TCCR0A_TypeDef;  // 0x0044

typedef volatile union {
	struct {
		uint8_t cs00 : 1;
		uint8_t cs01 : 1;
		uint8_t cs02 : 1;
		uint8_t wgm02 : 1;
		uint8_t : 2;
		uint8_t foc0b : 1;
		uint8_t foc0a : 1;
	} par;
	uint8_t var;
} _TCCR0B_TypeDef;  // 0x0045

typedef volatile union {
	struct {
		uint8_t b0 : 1; uint8_t b1 : 1; uint8_t b2 : 1; uint8_t b3 : 1;
		uint8_t b4 : 1; uint8_t b5 : 1; uint8_t b6 : 1; uint8_t b7 : 1;
	} par;
	uint8_t var;
} _TCNT0_TypeDef;  // 0x0046

typedef volatile union {
	struct {
		uint8_t b0 : 1; uint8_t b1 : 1; uint8_t b2 : 1; uint8_t b3 : 1;
		uint8_t b4 : 1; uint8_t b5 : 1; uint8_t b6 : 1; uint8_t b7 : 1;
	} par;
	uint8_t var;
} _OCR0A_TypeDef;  // 0x0047

typedef volatile union {
	struct {
		uint8_t b0 : 1; uint8_t b1 : 1; uint8_t b2 : 1; uint8_t b3 : 1;
		uint8_t b4 : 1; uint8_t b5 : 1; uint8_t b6 : 1; uint8_t b7 : 1;
	} par;
	uint8_t var;
} _OCR0B_TypeDef;  // 0x0048

/*** Timer0 Module Struct ***/
typedef struct {
	_TIFR0_TypeDef* tifr0;    // 0x0035 - Timer/Counter0 Interrupt Flag Register
	_TIMSK0_TypeDef* timsk0;  // 0x006E - Timer/Counter0 Interrupt Mask Register
	_TCCR0A_TypeDef* tccr0a;  // 0x0044 - Timer/Counter Control Register A
	_TCCR0B_TypeDef* tccr0b;  // 0x0045 - Timer/Counter Control Register B
	_TCNT0_TypeDef*  tcnt0;   // 0x0046 - Timer/Counter Register
	_OCR0A_TypeDef*  ocr0a;   // 0x0047 - Output Compare Register A
	_OCR0B_TypeDef*  ocr0b;   // 0x0048 - Output Compare Register B
} _TIMER0_Module;

/*** Initialization Function ***/
static _TIMER0_Module timer0_instance;

_TIMER0_Module* TIMER0_enable(void) {
	timer0_instance.tifr0  = (_TIFR0_TypeDef*) 0x0035;
	timer0_instance.timsk0 = (_TIMSK0_TypeDef*) 0x006E;
	timer0_instance.tccr0a = (_TCCR0A_TypeDef*) 0x0044;
	timer0_instance.tccr0b = (_TCCR0B_TypeDef*) 0x0045;
	timer0_instance.tcnt0  = (_TCNT0_TypeDef*) 0x0046;
	timer0_instance.ocr0a  = (_OCR0A_TypeDef*) 0x0047;
	timer0_instance.ocr0b  = (_OCR0B_TypeDef*) 0x0048;
	return &timer0_instance;
}
