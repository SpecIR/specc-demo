/**
 * @file alarm.h
 * @brief Alarm Unit
 *
 * Manages alarm time setting and triggering.
 * Supports one alarm with snooze functionality.
 */

#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>
#include "time_manager.h"

/* Alarm output peripheral */
#define ALARM_BASE      0x40021100

/* Static volatile pointer - declared in .c */
extern volatile uint32_t* const ALARM_BUZZER_REG;

/* Alarm state */
typedef enum {
    ALARM_STATE_OFF,        /* Alarm disabled */
    ALARM_STATE_ARMED,      /* Alarm set and waiting */
    ALARM_STATE_RINGING,    /* Alarm triggered, buzzer active */
    ALARM_STATE_SNOOZED,    /* Alarm snoozed */
} alarm_state_t;

/* Snooze duration in minutes */
#define ALARM_SNOOZE_MINUTES 5

/* Initialize alarm unit */
void alarm_init(void);

/* Set alarm time */
void alarm_set_time(const clock_time_t* time);

/* Get alarm time */
void alarm_get_time(clock_time_t* time);

/* Enable/disable alarm */
void alarm_enable(int enable);

/* Check if alarm is enabled */
int alarm_is_enabled(void);

/* Check current time and trigger alarm if needed - call each second */
void alarm_check(const clock_time_t* current_time);

/* Stop ringing (dismiss) */
void alarm_dismiss(void);

/* Snooze for ALARM_SNOOZE_MINUTES */
void alarm_snooze(void);

/* Get current alarm state */
alarm_state_t alarm_get_state(void);

/* Alarm time adjustment (for setting mode) */
void alarm_increment_hours(void);
void alarm_increment_minutes(void);
void alarm_decrement_hours(void);
void alarm_decrement_minutes(void);

#endif /* ALARM_H */
