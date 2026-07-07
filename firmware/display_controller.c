/**
 * @file display_controller.c
 * @brief Display Controller Implementation
 */

#include "display_controller.h"

/* Static volatile pointers for MMIO - AST-rewriter compatible */
volatile uint32_t* const DISPLAY_HOURS_HI_REG   = (volatile uint32_t*)(DISPLAY_BASE + 0x00);
volatile uint32_t* const DISPLAY_HOURS_LO_REG   = (volatile uint32_t*)(DISPLAY_BASE + 0x04);
volatile uint32_t* const DISPLAY_MINUTES_HI_REG = (volatile uint32_t*)(DISPLAY_BASE + 0x08);
volatile uint32_t* const DISPLAY_MINUTES_LO_REG = (volatile uint32_t*)(DISPLAY_BASE + 0x0C);
volatile uint32_t* const DISPLAY_COLON_REG      = (volatile uint32_t*)(DISPLAY_BASE + 0x10);
volatile uint32_t* const DISPLAY_CTRL_REG       = (volatile uint32_t*)(DISPLAY_BASE + 0x14);
volatile uint32_t* const DISPLAY_ALARM_LED_REG  = (volatile uint32_t*)(DISPLAY_BASE + 0x18);

static uint8_t colon_state = 0;

void display_init(void) {
    *DISPLAY_CTRL_REG = DISPLAY_CTRL_ENABLE;
    *DISPLAY_HOURS_HI_REG = 0;
    *DISPLAY_HOURS_LO_REG = 0;
    *DISPLAY_MINUTES_HI_REG = 0;
    *DISPLAY_MINUTES_LO_REG = 0;
    *DISPLAY_COLON_REG = 1;  /* Start with colon on */
    *DISPLAY_ALARM_LED_REG = 0;
    colon_state = 1;
}

uint8_t display_to_bcd(uint8_t value) {
    /* Convert binary to BCD: 23 -> 0x23 (2 in high nibble, 3 in low nibble) */
    uint8_t tens = value / 10;
    uint8_t ones = value % 10;
    return (tens << 4) | ones;
}

void display_update(uint8_t hours, uint8_t minutes) {
    /* Convert to BCD and write to individual digit registers */
    *DISPLAY_HOURS_HI_REG = hours / 10;
    *DISPLAY_HOURS_LO_REG = hours % 10;
    *DISPLAY_MINUTES_HI_REG = minutes / 10;
    *DISPLAY_MINUTES_LO_REG = minutes % 10;
}

void display_toggle_colon(void) {
    colon_state = !colon_state;
    *DISPLAY_COLON_REG = colon_state;
}

void display_set_blink(int enable) {
    if (enable) {
        *DISPLAY_CTRL_REG |= DISPLAY_CTRL_BLINK_ON;
    } else {
        *DISPLAY_CTRL_REG &= ~DISPLAY_CTRL_BLINK_ON;
    }
}

void display_set_alarm_led(int on) {
    *DISPLAY_ALARM_LED_REG = on ? 1 : 0;
}
