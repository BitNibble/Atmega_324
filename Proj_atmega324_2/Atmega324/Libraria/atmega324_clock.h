#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>
#include <stdbool.h>

// Sleep modes bits for MCUCR register
typedef enum {
    SLEEP_MODE_IDLE          = 0x00, // SM2=0, SM1=0, SM0=0
    SLEEP_MODE_ADC           = 0x08, // SM2=0, SM1=0, SM0=1
    SLEEP_MODE_PWR_SAVE      = 0x09, // SM2=0, SM1=1, SM0=0
    SLEEP_MODE_STANDBY       = 0x0A, // SM2=0, SM1=1, SM0=1
    SLEEP_MODE_EXT_STANDBY   = 0x0B, // SM2=1, SM1=0, SM0=0
} SleepMode_t;

// Initialize clock prescaler (division factor: 1,2,4,8,16,32,64,128,256)
bool clock_set_prescaler(uint8_t division_factor);

// Get current clock prescaler division factor
uint8_t clock_get_prescaler(void);

// Set sleep mode (must be called before entering sleep)
void clock_set_sleep_mode(SleepMode_t mode);

// Enter sleep mode (CPU will sleep until interrupt)
void clock_enter_sleep(void);

// Enable power reduction bits (PRR0 and PRR1)
void clock_power_reduce_enable(uint16_t prr_mask);

// Disable power reduction bits (PRR0 and PRR1)
void clock_power_reduce_disable(uint16_t prr_mask);

#endif // CLOCK_H
