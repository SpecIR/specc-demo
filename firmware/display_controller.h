/**
 * @file display_controller.h
 * @brief Display Controller
 *
 * Handles conversion of time values to BCD format for 7-segment displays.
 * Manages display peripheral registers.
 */

#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <stdint.h>

/* Display peripheral base address */
#define DISPLAY_BASE        0x40021000

/* Control register bits (enum for AST-rewriter compatibility) */
enum {
    DISPLAY_CTRL_ENABLE   = 1 << 0,
    DISPLAY_CTRL_BLINK_ON = 1 << 1   /* Blink when in set mode */
};

/* Static volatile pointers - declared in .c, used here for reference */
extern volatile uint32_t* const DISPLAY_HOURS_HI_REG;
extern volatile uint32_t* const DISPLAY_HOURS_LO_REG;
extern volatile uint32_t* const DISPLAY_MINUTES_HI_REG;
extern volatile uint32_t* const DISPLAY_MINUTES_LO_REG;
extern volatile uint32_t* const DISPLAY_COLON_REG;
extern volatile uint32_t* const DISPLAY_CTRL_REG;
extern volatile uint32_t* const DISPLAY_ALARM_LED_REG;

/* Initialize display controller */
void display_init(void);

/* Update display with hours and minutes */
void display_update(uint8_t hours, uint8_t minutes);

/* Toggle colon (call each second for blinking effect) */
void display_toggle_colon(void);

/* Set blink mode (for time setting) */
void display_set_blink(int enable);

/* Set alarm LED state */
void display_set_alarm_led(int on);

/* Convert binary value to BCD */
uint8_t display_to_bcd(uint8_t value);

#endif /* DISPLAY_CONTROLLER_H */
