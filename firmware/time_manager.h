/**
 * @file time_manager.h
 * @brief Time Management Unit
 *
 * Handles tick-to-time conversion and time state management.
 * Provides API for time setting via external inputs (buttons).
 */

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <stdint.h>

/* Time structure (named clock_time_t to avoid conflict with stdlib time_t) */
typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} clock_time_t;

/* Time manager initialization */
void time_manager_init(void);

/* Tick handling - call from SysTick ISR */
void time_manager_tick(void);

/* Get current time */
void time_manager_get_time(clock_time_t* time);

/* Set current time */
void time_manager_set_time(const clock_time_t* time);

/* Increment functions for button control */
void time_manager_increment_hours(void);
void time_manager_increment_minutes(void);
void time_manager_decrement_hours(void);
void time_manager_decrement_minutes(void);

/* Get raw tick count for debugging */
uint32_t time_manager_get_ticks(void);

/* Ticks per second (configurable for testing) */
#define TIME_MANAGER_TICKS_PER_SECOND 1000

#endif /* TIME_MANAGER_H */
