/**
 * @file clock_main.h
 * @brief Digital Clock Main Integration
 *
 * Integrates all modules and manages the clock state machine.
 * Handles UI modes: Normal, Set Time, Set Alarm
 */

#ifndef CLOCK_MAIN_H
#define CLOCK_MAIN_H

#include <stdint.h>

/* Cortex-M SysTick registers */
#define SYSTICK_BASE    0xE000E010

/* SysTick control bits (enum for AST-rewriter compatibility) */
enum {
    SYSTICK_ENABLE    = 1 << 0,
    SYSTICK_TICKINT   = 1 << 1,
    SYSTICK_CLKSOURCE = 1 << 2
};

/* Static volatile pointers - declared in .c */
extern volatile uint32_t* const SYSTICK_CTRL_REG;
extern volatile uint32_t* const SYSTICK_LOAD_REG;
extern volatile uint32_t* const SYSTICK_VAL_REG;

/* Clock modes (UI state machine) */
typedef enum {
    CLOCK_MODE_NORMAL,      /* Normal time display */
    CLOCK_MODE_SET_TIME,    /* Setting current time */
    CLOCK_MODE_SET_ALARM,   /* Setting alarm time */
} clock_mode_t;

/* Currently editing field (hours or minutes) */
typedef enum {
    CLOCK_EDIT_HOURS,
    CLOCK_EDIT_MINUTES,
} clock_edit_field_t;

/* Initialize entire clock system */
void clock_init(void);

/* Main processing (call from main loop or SysTick) */
void clock_process(void);

/* Get current clock mode */
clock_mode_t clock_get_mode(void);

/* Get current edit field (when in set mode) */
clock_edit_field_t clock_get_edit_field(void);

/* SysTick interrupt handler - declared for external linkage */
void SysTick_Handler(void);

#endif /* CLOCK_MAIN_H */
