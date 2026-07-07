/**
 * @file button_controller.h
 * @brief Button Controller
 *
 * Handles two buttons with debouncing, short press, and long press detection.
 * Button A: Mode/Select, Button B: Adjust/Confirm
 */

#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <stdint.h>

/* Button peripheral addresses */
#define BUTTON_BASE     0x40020100

/* Static volatile pointers - declared in .c */
extern volatile uint32_t* const BUTTON_A_PTR;
extern volatile uint32_t* const BUTTON_B_PTR;

/* Button events (returned by button_controller_get_event) */
typedef enum {
    BUTTON_EVENT_NONE = 0,
    BUTTON_EVENT_A_SHORT,   /* Button A short press */
    BUTTON_EVENT_A_LONG,    /* Button A long press (held > threshold) */
    BUTTON_EVENT_B_SHORT,   /* Button B short press */
    BUTTON_EVENT_B_LONG,    /* Button B long press */
} button_event_t;

/* Timing constants (in ticks, assuming 1ms tick) */
#define BUTTON_DEBOUNCE_TICKS   50   /* 50ms debounce */
#define BUTTON_LONG_PRESS_TICKS 1000 /* 1 second for long press */

/* Initialize button controller */
void button_controller_init(void);

/* Process buttons - call from SysTick ISR */
void button_controller_tick(void);

/* Get the next pending button event (consumes the event) */
button_event_t button_controller_get_event(void);

/* Check if any button is currently pressed (for UI feedback) */
int button_controller_any_pressed(void);

/* Get raw button states (for debugging) */
int button_controller_is_a_pressed(void);
int button_controller_is_b_pressed(void);

#endif /* BUTTON_CONTROLLER_H */
