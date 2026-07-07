## Símbolos Extraídos do Código-Fonte

Os objetos a seguir foram gerados automaticamente a partir da análise estática das unidades de compilação (libclang).

### SYMBOL: SysTick_Handler @SysTick_Handler

> kind: function

> source: firmware/clock_main.c:199:1-210:2

> complexity: 1

> calls: [button_controller_tick](@), [clock_process](@), [time_manager_tick](@)

### SYMBOL: alarm_check @alarm_check

> kind: function

> source: firmware/alarm.c:56:1-68:2

> complexity: 5

> calls: [time_matches](@)

### SYMBOL: alarm_decrement_hours @alarm_decrement_hours

> kind: function

> source: firmware/alarm.c:107:1-113:2

> complexity: 2

### SYMBOL: alarm_decrement_minutes @alarm_decrement_minutes

> kind: function

> source: firmware/alarm.c:115:1-121:2

> complexity: 2

### SYMBOL: alarm_dismiss @alarm_dismiss

> kind: function

> source: firmware/alarm.c:70:1-75:2

> complexity: 2

### SYMBOL: alarm_enable @alarm_enable

> kind: function

> source: firmware/alarm.c:38:1-46:2

> complexity: 3

### SYMBOL: alarm_get_state @alarm_get_state

> kind: function

> source: firmware/alarm.c:95:1-97:2

> complexity: 1

### SYMBOL: alarm_get_time @alarm_get_time

> kind: function

> source: firmware/alarm.c:32:1-36:2

> complexity: 1

### SYMBOL: alarm_increment_hours @alarm_increment_hours

> kind: function

> source: firmware/alarm.c:99:1-101:2

> complexity: 1

### SYMBOL: alarm_increment_minutes @alarm_increment_minutes

> kind: function

> source: firmware/alarm.c:103:1-105:2

> complexity: 1

### SYMBOL: alarm_init @alarm_init

> kind: function

> source: firmware/alarm.c:17:1-24:2

> complexity: 1

### SYMBOL: alarm_is_enabled @alarm_is_enabled

> kind: function

> source: firmware/alarm.c:48:1-50:2

> complexity: 1

### SYMBOL: alarm_set_time @alarm_set_time

> kind: function

> source: firmware/alarm.c:26:1-30:2

> complexity: 1

### SYMBOL: alarm_snooze @alarm_snooze

> kind: function

> source: firmware/alarm.c:77:1-93:2

> complexity: 3

### SYMBOL: button_controller_any_pressed @button_controller_any_pressed

> kind: function

> source: firmware/button_controller.c:135:1-140:2

> complexity: 1

### SYMBOL: button_controller_get_event @button_controller_get_event

> kind: function

> source: firmware/button_controller.c:129:1-133:2

> complexity: 1

### SYMBOL: button_controller_init @button_controller_init

> kind: function

> source: firmware/button_controller.c:97:1-109:2

> complexity: 1

### SYMBOL: button_controller_is_a_pressed @button_controller_is_a_pressed

> kind: function

> source: firmware/button_controller.c:142:1-145:2

> complexity: 1

### SYMBOL: button_controller_is_b_pressed @button_controller_is_b_pressed

> kind: function

> source: firmware/button_controller.c:147:1-150:2

> complexity: 1

### SYMBOL: button_controller_tick @button_controller_tick

> kind: function

> source: firmware/button_controller.c:111:1-127:2

> complexity: 3

> calls: [process_button](@), [read_button_a](@), [read_button_b](@)

### SYMBOL: clock_get_edit_field @clock_get_edit_field

> kind: function

> source: firmware/clock_main.c:190:1-192:2

> complexity: 1

### SYMBOL: clock_get_mode @clock_get_mode

> kind: function

> source: firmware/clock_main.c:186:1-188:2

> complexity: 1

### SYMBOL: clock_init @clock_init

> kind: function

> source: firmware/clock_main.c:133:1-153:2

> complexity: 1

> calls: [alarm_init](@), [button_controller_init](@), [display_init](@), [time_manager_init](@), [update_display](@)

### SYMBOL: clock_process @clock_process

> kind: function

> source: firmware/clock_main.c:155:1-184:2

> complexity: 3

> calls: [alarm_check](@), [alarm_get_state](@), [alarm_is_enabled](@), [button_controller_get_event](@), [display_set_alarm_led](@), [display_toggle_colon](@), [handle_button_event](@), [time_manager_get_time](@), [update_display](@)

### SYMBOL: display_init @display_init

> kind: function

> source: firmware/display_controller.c:19:1-28:2

> complexity: 1

### SYMBOL: display_set_alarm_led @display_set_alarm_led

> kind: function

> source: firmware/display_controller.c:58:1-60:2

> complexity: 2

### SYMBOL: display_set_blink @display_set_blink

> kind: function

> source: firmware/display_controller.c:50:1-56:2

> complexity: 2

### SYMBOL: display_to_bcd @display_to_bcd

> kind: function

> source: firmware/display_controller.c:30:1-35:2

> complexity: 1

### SYMBOL: display_toggle_colon @display_toggle_colon

> kind: function

> source: firmware/display_controller.c:45:1-48:2

> complexity: 1

### SYMBOL: display_update @display_update

> kind: function

> source: firmware/display_controller.c:37:1-43:2

> complexity: 1

### SYMBOL: handle_button_event @handle_button_event

> kind: function

> source: firmware/clock_main.c:24:1-113:2

> complexity: 24

> calls: [alarm_decrement_hours](@), [alarm_decrement_minutes](@), [alarm_enable](@), [alarm_get_state](@), [alarm_increment_hours](@), [alarm_increment_minutes](@), [alarm_is_enabled](@), [alarm_snooze](@), [display_set_alarm_led](@), [display_set_blink](@), [time_manager_decrement_hours](@), [time_manager_decrement_minutes](@), [time_manager_increment_hours](@), [time_manager_increment_minutes](@)

### SYMBOL: process_button @process_button

> kind: function

> source: firmware/button_controller.c:43:1-95:2

> complexity: 11

### SYMBOL: read_button_a @read_button_a

> kind: function

> source: firmware/button_controller.c:34:1-36:2

> complexity: 1

### SYMBOL: read_button_b @read_button_b

> kind: function

> source: firmware/button_controller.c:38:1-40:2

> complexity: 1

### SYMBOL: time_manager_decrement_hours @time_manager_decrement_hours

> kind: function

> source: firmware/time_manager.c:63:1-69:2

> complexity: 2

### SYMBOL: time_manager_decrement_minutes @time_manager_decrement_minutes

> kind: function

> source: firmware/time_manager.c:71:1-77:2

> complexity: 2

### SYMBOL: time_manager_get_ticks @time_manager_get_ticks

> kind: function

> source: firmware/time_manager.c:79:1-81:2

> complexity: 1

### SYMBOL: time_manager_get_time @time_manager_get_time

> kind: function

> source: firmware/time_manager.c:42:1-46:2

> complexity: 1

### SYMBOL: time_manager_increment_hours @time_manager_increment_hours

> kind: function

> source: firmware/time_manager.c:55:1-57:2

> complexity: 1

### SYMBOL: time_manager_increment_minutes @time_manager_increment_minutes

> kind: function

> source: firmware/time_manager.c:59:1-61:2

> complexity: 1

### SYMBOL: time_manager_init @time_manager_init

> kind: function

> source: firmware/time_manager.c:12:1-17:2

> complexity: 1

### SYMBOL: time_manager_set_time @time_manager_set_time

> kind: function

> source: firmware/time_manager.c:48:1-53:2

> complexity: 1

### SYMBOL: time_manager_tick @time_manager_tick

> kind: function

> source: firmware/time_manager.c:19:1-40:2

> complexity: 5

### SYMBOL: time_matches @time_matches

> kind: function

> source: firmware/alarm.c:52:1-54:2

> complexity: 1

### SYMBOL: update_display @update_display

> kind: function

> source: firmware/clock_main.c:116:1-131:2

> complexity: 4

> calls: [alarm_get_time](@), [display_update](@), [time_manager_get_time](@)

