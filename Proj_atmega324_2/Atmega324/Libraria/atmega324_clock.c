#include "clock.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Set CPU clock prescaler (division factor must be valid)
bool clock_set_prescaler(uint8_t division_factor) {
    uint8_t clkpr_bits;

    switch (division_factor) {
        case 1:   clkpr_bits = 0; break;
        case 2:   clkpr_bits = 1; break;
        case 4:   clkpr_bits = 2; break;
        case 8:   clkpr_bits = 3; break;
        case 16:  clkpr_bits = 4; break;
        case 32:  clkpr_bits = 5; break;
        case 64:  clkpr_bits = 6; break;
        case 128: clkpr_bits = 7; break;
        case 256: clkpr_bits = 8; break;
        default:
            return false; // invalid division factor
    }

    cli();              // Disable interrupts
    CLKPR = (1 << CLKPCE);  // Enable change of CLKPR
    CLKPR = clkpr_bits;      // Set prescaler bits
    sei();              // Enable interrupts

    return true;
}

uint8_t clock_get_prescaler(void) {
    uint8_t bits = CLKPR & 0x0F;
    switch(bits) {
        case 0: return 1;
        case 1: return 2;
        case 2: return 4;
        case 3: return 8;
        case 4: return 16;
        case 5: return 32;
        case 6: return 64;
        case 7: return 128;
        case 8: return 256;
        default: return 1;
    }
}

void clock_set_sleep_mode(SleepMode_t mode) {
    // Clear previous SM bits (bits 5,4,3) in MCUCR and set new mode
    MCUCR = (MCUCR & ~(0x38)) | (mode << 3);
}

void clock_enter_sleep(void) {
    set_sleep_mode(SLEEP_MODE_IDLE);  // Default fallback if user forgets
    sleep_enable();
    sleep_cpu();
    sleep_disable();
}

void clock_power_reduce_enable(uint16_t prr_mask) {
    // PRR0 and PRR1 are two 8-bit registers; mask LSB for PRR0, MSB for PRR1
    if (prr_mask & 0x00FF) {
        PRR0 |= (uint8_t)(prr_mask & 0x00FF);
    }
    if (prr_mask & 0xFF00) {
        PRR1 |= (uint8_t)((prr_mask >> 8) & 0x00FF);
    }
}

void clock_power_reduce_disable(uint16_t prr_mask) {
    if (prr_mask & 0x00FF) {
        PRR0 &= ~((uint8_t)(prr_mask & 0x00FF));
    }
    if (prr_mask & 0xFF00) {
        PRR1 &= ~((uint8_t)((prr_mask >> 8) & 0x00FF));
    }
}
