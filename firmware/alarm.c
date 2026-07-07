/**
 * @file alarm.c
 * @brief Alarm Unit Implementation
 */

#include "alarm.h"

/* Static volatile pointer for MMIO - AST-rewriter compatible */
volatile uint32_t* const ALARM_BUZZER_REG = (volatile uint32_t*)(ALARM_BASE + 0x00);

/* Alarm state */
static clock_time_t alarm_time = {0, 0, 0};
static alarm_state_t alarm_state = ALARM_STATE_OFF;
static clock_time_t snooze_time = {0, 0, 0};
static int alarm_enabled = 0;

void alarm_init(void) {
    alarm_time.hours = 7;    /* Default alarm: 7:00 AM */
    alarm_time.minutes = 0;
    alarm_time.seconds = 0;
    alarm_state = ALARM_STATE_OFF;
    alarm_enabled = 0;
    *ALARM_BUZZER_REG = 0;
}

void alarm_set_time(const clock_time_t* time) {
    alarm_time.hours = time->hours % 24;
    alarm_time.minutes = time->minutes % 60;
    alarm_time.seconds = 0;  /* Alarm ignores seconds */
}

void alarm_get_time(clock_time_t* time) {
    time->hours = alarm_time.hours;
    time->minutes = alarm_time.minutes;
    time->seconds = 0;
}

void alarm_enable(int enable) {
    alarm_enabled = enable;
    if (enable && alarm_state == ALARM_STATE_OFF) {
        alarm_state = ALARM_STATE_ARMED;
    } else if (!enable) {
        alarm_state = ALARM_STATE_OFF;
        *ALARM_BUZZER_REG = 0;
    }
}

int alarm_is_enabled(void) {
    return alarm_enabled;
}

static int time_matches(const clock_time_t* a, const clock_time_t* b) {
    return (a->hours == b->hours && a->minutes == b->minutes);
}

void alarm_check(const clock_time_t* current_time) {
    if (alarm_state == ALARM_STATE_ARMED) {
        if (time_matches(current_time, &alarm_time)) {
            alarm_state = ALARM_STATE_RINGING;
            *ALARM_BUZZER_REG = 1;
        }
    } else if (alarm_state == ALARM_STATE_SNOOZED) {
        if (time_matches(current_time, &snooze_time)) {
            alarm_state = ALARM_STATE_RINGING;
            *ALARM_BUZZER_REG = 1;
        }
    }
}

void alarm_dismiss(void) {
    if (alarm_state == ALARM_STATE_RINGING || alarm_state == ALARM_STATE_SNOOZED) {
        alarm_state = ALARM_STATE_ARMED;  /* Re-arm for next day */
        *ALARM_BUZZER_REG = 0;
    }
}

void alarm_snooze(void) {
    if (alarm_state == ALARM_STATE_RINGING) {
        /* Calculate snooze time */
        snooze_time.hours = alarm_time.hours;
        snooze_time.minutes = alarm_time.minutes + ALARM_SNOOZE_MINUTES;
        snooze_time.seconds = 0;

        /* Handle minute overflow */
        if (snooze_time.minutes >= 60) {
            snooze_time.minutes -= 60;
            snooze_time.hours = (snooze_time.hours + 1) % 24;
        }

        alarm_state = ALARM_STATE_SNOOZED;
        *ALARM_BUZZER_REG = 0;
    }
}

alarm_state_t alarm_get_state(void) {
    return alarm_state;
}

void alarm_increment_hours(void) {
    alarm_time.hours = (alarm_time.hours + 1) % 24;
}

void alarm_increment_minutes(void) {
    alarm_time.minutes = (alarm_time.minutes + 1) % 60;
}

void alarm_decrement_hours(void) {
    if (alarm_time.hours == 0) {
        alarm_time.hours = 23;
    } else {
        alarm_time.hours--;
    }
}

void alarm_decrement_minutes(void) {
    if (alarm_time.minutes == 0) {
        alarm_time.minutes = 59;
    } else {
        alarm_time.minutes--;
    }
}
