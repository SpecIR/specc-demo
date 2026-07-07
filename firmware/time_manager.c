/**
 * @file time_manager.c
 * @brief Time Management Unit Implementation
 */

#include "time_manager.h"

/* Internal state */
static volatile uint32_t tick_count = 0;
static volatile clock_time_t current_time = {0, 0, 0};

void time_manager_init(void) {
    tick_count = 0;
    current_time.hours = 0;
    current_time.minutes = 0;
    current_time.seconds = 0;
}

void time_manager_tick(void) {
    tick_count++;

    if (tick_count >= TIME_MANAGER_TICKS_PER_SECOND) {
        tick_count = 0;
        current_time.seconds++;

        if (current_time.seconds >= 60) {
            current_time.seconds = 0;
            current_time.minutes++;

            if (current_time.minutes >= 60) {
                current_time.minutes = 0;
                current_time.hours++;

                if (current_time.hours >= 24) {
                    current_time.hours = 0;
                }
            }
        }
    }
}

void time_manager_get_time(clock_time_t* time) {
    time->hours = current_time.hours;
    time->minutes = current_time.minutes;
    time->seconds = current_time.seconds;
}

void time_manager_set_time(const clock_time_t* time) {
    current_time.hours = time->hours % 24;
    current_time.minutes = time->minutes % 60;
    current_time.seconds = time->seconds % 60;
    tick_count = 0;
}

void time_manager_increment_hours(void) {
    current_time.hours = (current_time.hours + 1) % 24;
}

void time_manager_increment_minutes(void) {
    current_time.minutes = (current_time.minutes + 1) % 60;
}

void time_manager_decrement_hours(void) {
    if (current_time.hours == 0) {
        current_time.hours = 23;
    } else {
        current_time.hours--;
    }
}

void time_manager_decrement_minutes(void) {
    if (current_time.minutes == 0) {
        current_time.minutes = 59;
    } else {
        current_time.minutes--;
    }
}

uint32_t time_manager_get_ticks(void) {
    return tick_count;
}
