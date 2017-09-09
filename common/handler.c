#include "pic.h"
#include "sleep.h"
#include "os_life.h"
#include "io_commands.h"
#include "tetris.h"
#include "keyboard_codes.h"

unsigned char cur_pressed_button() {
	return inb(0x60);
}

extern my_state lifestatus;

void key_pressed_handler() {
	unsigned char pressed = cur_pressed_button();
	if (lifestatus == SLEEPING) {
		if (pressed == CODE_R) {
			lifestatus = WORKING;
		}
	} else {
		tetris_on_key_pressed(pressed);
	}
	pic_send_eoi(0x1);
}

extern unsigned long long lifetime;

void timer_tick_handler() {
	++lifetime;
	pic_send_eoi(0x0);
}
