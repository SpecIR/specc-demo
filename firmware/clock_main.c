/**
 * @file clock_main.c
 * @brief Digital Clock Main Integration Implementation
 */

#include "clock_main.h"
#include "time_manager.h"
#include "display_controller.h"
#include "button_controller.h"
#include "alarm.h"

/* Static volatile pointers for MMIO - AST-rewriter compatible */
volatile uint32_t* const SYSTICK_CTRL_REG = (volatile uint32_t*)(SYSTICK_BASE + 0x00);
volatile uint32_t* const SYSTICK_LOAD_REG = (volatile uint32_t*)(SYSTICK_BASE + 0x04);
volatile uint32_t* const SYSTICK_VAL_REG  = (volatile uint32_t*)(SYSTICK_BASE + 0x08);

/* Clock state */
static clock_mode_t current_mode = CLOCK_MODE_NORMAL;
static clock_edit_field_t edit_field = CLOCK_EDIT_HOURS;
static uint32_t tick_counter = 0;
static uint8_t last_seconds = 0;

/* Process button events based on current mode */
static void handle_button_event(button_event_t event) {
    if (event == BUTTON_EVENT_NONE) {
        return;
    }

    switch (current_mode) {
        case CLOCK_MODE_NORMAL:
            if (event == BUTTON_EVENT_A_LONG) {
                /* Long press A: Enter time set mode */
                current_mode = CLOCK_MODE_SET_TIME;
                edit_field = CLOCK_EDIT_HOURS;
                display_set_blink(1);
            } else if (event == BUTTON_EVENT_B_LONG) {
                /* Long press B: Enter alarm set mode */
                current_mode = CLOCK_MODE_SET_ALARM;
                edit_field = CLOCK_EDIT_HOURS;
                display_set_blink(1);
            } else if (event == BUTTON_EVENT_A_SHORT) {
                /* Short press A: Toggle alarm on/off */
                alarm_enable(!alarm_is_enabled());
                display_set_alarm_led(alarm_is_enabled());
            } else if (event == BUTTON_EVENT_B_SHORT) {
                /* Short press B: Snooze if alarm ringing, else nothing */
                if (alarm_get_state() == ALARM_STATE_RINGING) {
                    alarm_snooze();
                }
            }
            break;

        case CLOCK_MODE_SET_TIME:
            if (event == BUTTON_EVENT_A_SHORT) {
                /* Short A: Switch between hours/minutes */
                if (edit_field == CLOCK_EDIT_HOURS) {
                    edit_field = CLOCK_EDIT_MINUTES;
                } else {
                    edit_field = CLOCK_EDIT_HOURS;
                }
            } else if (event == BUTTON_EVENT_A_LONG) {
                /* Long A: Confirm and exit */
                current_mode = CLOCK_MODE_NORMAL;
                display_set_blink(0);
            } else if (event == BUTTON_EVENT_B_SHORT) {
                /* Short B: Increment current field */
                if (edit_field == CLOCK_EDIT_HOURS) {
                    time_manager_increment_hours();
                } else {
                    time_manager_increment_minutes();
                }
            } else if (event == BUTTON_EVENT_B_LONG) {
                /* Long B: Decrement current field */
                if (edit_field == CLOCK_EDIT_HOURS) {
                    time_manager_decrement_hours();
                } else {
                    time_manager_decrement_minutes();
                }
            }
            break;

        case CLOCK_MODE_SET_ALARM:
            if (event == BUTTON_EVENT_A_SHORT) {
                /* Short A: Switch between hours/minutes */
                if (edit_field == CLOCK_EDIT_HOURS) {
                    edit_field = CLOCK_EDIT_MINUTES;
                } else {
                    edit_field = CLOCK_EDIT_HOURS;
                }
            } else if (event == BUTTON_EVENT_A_LONG) {
                /* Long A: Confirm, enable alarm, and exit */
                alarm_enable(1);
                display_set_alarm_led(1);
                current_mode = CLOCK_MODE_NORMAL;
                display_set_blink(0);
            } else if (event == BUTTON_EVENT_B_SHORT) {
                /* Short B: Increment current field */
                if (edit_field == CLOCK_EDIT_HOURS) {
                    alarm_increment_hours();
                } else {
                    alarm_increment_minutes();
                }
            } else if (event == BUTTON_EVENT_B_LONG) {
                /* Long B: Decrement current field */
                if (edit_field == CLOCK_EDIT_HOURS) {
                    alarm_decrement_hours();
                } else {
                    alarm_decrement_minutes();
                }
            }
            break;
    }
}

/* Update display based on current mode */
static void update_display(void) {
    clock_time_t time;

    switch (current_mode) {
        case CLOCK_MODE_NORMAL:
        case CLOCK_MODE_SET_TIME:
            time_manager_get_time(&time);
            display_update(time.hours, time.minutes);
            break;

        case CLOCK_MODE_SET_ALARM:
            alarm_get_time(&time);
            display_update(time.hours, time.minutes);
            break;
    }
}

void clock_init(void) {
    /* Initialize all modules */
    time_manager_init();
    display_init();
    button_controller_init();
    alarm_init();

    /* Configure SysTick for 1ms tick (assuming 8MHz clock) */
    *SYSTICK_LOAD_REG = 8000 - 1;
    *SYSTICK_VAL_REG = 0;
    *SYSTICK_CTRL_REG = SYSTICK_ENABLE | SYSTICK_TICKINT | SYSTICK_CLKSOURCE;

    /* Initial state */
    current_mode = CLOCK_MODE_NORMAL;
    edit_field = CLOCK_EDIT_HOURS;
    tick_counter = 0;
    last_seconds = 0;

    /* Initial display */
    update_display();
}

void clock_process(void) {
    clock_time_t time;
    button_event_t event;

    /* Get and handle button events */
    event = button_controller_get_event();
    handle_button_event(event);

    /* Check for second boundary for display and alarm updates */
    time_manager_get_time(&time);

    if (time.seconds != last_seconds) {
        last_seconds = time.seconds;

        /* Toggle colon each second (in normal mode) */
        if (current_mode == CLOCK_MODE_NORMAL) {
            display_toggle_colon();
        }

        /* Check alarm */
        alarm_check(&time);

        /* Update display */
        update_display();
    }

    /* Update alarm LED state */
    display_set_alarm_led(alarm_is_enabled() ||
                          alarm_get_state() == ALARM_STATE_RINGING);
}

clock_mode_t clock_get_mode(void) {
    return current_mode;
}

clock_edit_field_t clock_get_edit_field(void) {
    return edit_field;
}

/**
 * @brief SysTick interrupt handler
 *
 * Called every 1ms to update time and process buttons.
 */
void SysTick_Handler(void) {
    tick_counter++;

    /* Update time each tick */
    time_manager_tick();

    /* Process buttons each tick */
    button_controller_tick();

    /* Main clock processing */
    clock_process();
}
