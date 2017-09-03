#include "handler.h"
#include "io_commands.h"
#include "keyboard_codes.h"
#include "types.h"
#include "os_life.h"

#pragma mark - keyboard handler

uint8_t cur_button_key() {
	return inb(0x60);
}

extern my_status lifestatus;

void key_pressed_handler() {
	uint8_t c = cur_button_key();
	if (c == CODE_R && lifestatus == SLEEPING) {
		lifestatus = WORKING;
		//call tetris function to start game
	} else {
		//call tetris function to work with input
	}
	PIC_sendEOI(0x1);
}

#pragma mark - timer handler

extern uint64_t lifetime;

void timer_tick_handler() {
	++lifetime;
	PIC_sendEOI(0x0);
}
