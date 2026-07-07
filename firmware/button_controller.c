/**
 * @file button_controller.c
 * @brief Button Controller Implementation
 */

#include "button_controller.h"

/* Static volatile pointers for MMIO - AST-rewriter compatible */
volatile uint32_t* const BUTTON_A_PTR = (volatile uint32_t*)(BUTTON_BASE + 0x00);
volatile uint32_t* const BUTTON_B_PTR = (volatile uint32_t*)(BUTTON_BASE + 0x04);

/* Button state machine states */
typedef enum {
    BTN_STATE_IDLE,
    BTN_STATE_DEBOUNCE,
    BTN_STATE_PRESSED,
    BTN_STATE_LONG_PRESS_SENT,
} button_state_t;

/* Per-button state */
typedef struct {
    button_state_t state;
    uint16_t debounce_counter;
    uint16_t hold_counter;
    uint8_t last_raw;
} button_ctx_t;

/* Module state */
static button_ctx_t btn_a = {0};
static button_ctx_t btn_b = {0};
static volatile button_event_t pending_event = BUTTON_EVENT_NONE;

/* Read raw button state (active high) */
static int read_button_a(void) {
    return (*BUTTON_A_PTR & 0x01) != 0;
}

static int read_button_b(void) {
    return (*BUTTON_B_PTR & 0x01) != 0;
}

/* Process a single button */
static button_event_t process_button(button_ctx_t* ctx, int raw,
                                     button_event_t short_evt,
                                     button_event_t long_evt) {
    button_event_t evt = BUTTON_EVENT_NONE;

    switch (ctx->state) {
        case BTN_STATE_IDLE:
            if (raw && !ctx->last_raw) {
                /* Rising edge - start debounce */
                ctx->state = BTN_STATE_DEBOUNCE;
                ctx->debounce_counter = 0;
            }
            break;

        case BTN_STATE_DEBOUNCE:
            ctx->debounce_counter++;
            if (!raw) {
                /* Button released during debounce - bounce detected */
                ctx->state = BTN_STATE_IDLE;
            } else if (ctx->debounce_counter >= BUTTON_DEBOUNCE_TICKS) {
                /* Debounce complete - button is pressed */
                ctx->state = BTN_STATE_PRESSED;
                ctx->hold_counter = 0;
            }
            break;

        case BTN_STATE_PRESSED:
            if (!raw) {
                /* Button released - short press */
                evt = short_evt;
                ctx->state = BTN_STATE_IDLE;
            } else {
                ctx->hold_counter++;
                if (ctx->hold_counter >= BUTTON_LONG_PRESS_TICKS) {
                    /* Long press threshold reached */
                    evt = long_evt;
                    ctx->state = BTN_STATE_LONG_PRESS_SENT;
                }
            }
            break;

        case BTN_STATE_LONG_PRESS_SENT:
            if (!raw) {
                /* Button released after long press */
                ctx->state = BTN_STATE_IDLE;
            }
            /* Ignore further holds after long press event sent */
            break;
    }

    ctx->last_raw = raw;
    return evt;
}

void button_controller_init(void) {
    btn_a.state = BTN_STATE_IDLE;
    btn_a.debounce_counter = 0;
    btn_a.hold_counter = 0;
    btn_a.last_raw = 0;

    btn_b.state = BTN_STATE_IDLE;
    btn_b.debounce_counter = 0;
    btn_b.hold_counter = 0;
    btn_b.last_raw = 0;

    pending_event = BUTTON_EVENT_NONE;
}

void button_controller_tick(void) {
    button_event_t evt;

    /* Process button A */
    evt = process_button(&btn_a, read_button_a(),
                         BUTTON_EVENT_A_SHORT, BUTTON_EVENT_A_LONG);
    if (evt != BUTTON_EVENT_NONE && pending_event == BUTTON_EVENT_NONE) {
        pending_event = evt;
    }

    /* Process button B */
    evt = process_button(&btn_b, read_button_b(),
                         BUTTON_EVENT_B_SHORT, BUTTON_EVENT_B_LONG);
    if (evt != BUTTON_EVENT_NONE && pending_event == BUTTON_EVENT_NONE) {
        pending_event = evt;
    }
}

button_event_t button_controller_get_event(void) {
    button_event_t evt = pending_event;
    pending_event = BUTTON_EVENT_NONE;
    return evt;
}

int button_controller_any_pressed(void) {
    return (btn_a.state == BTN_STATE_PRESSED ||
            btn_a.state == BTN_STATE_LONG_PRESS_SENT ||
            btn_b.state == BTN_STATE_PRESSED ||
            btn_b.state == BTN_STATE_LONG_PRESS_SENT);
}

int button_controller_is_a_pressed(void) {
    return (btn_a.state == BTN_STATE_PRESSED ||
            btn_a.state == BTN_STATE_LONG_PRESS_SENT);
}

int button_controller_is_b_pressed(void) {
    return (btn_b.state == BTN_STATE_PRESSED ||
            btn_b.state == BTN_STATE_LONG_PRESS_SENT);
}
