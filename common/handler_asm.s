.global key_pressed_asm
.type key_pressed_asm, @function
key_pressed_asm:
	pushal
	call key_pressed_handler
	popal
	iret

.global timer_tick_asm
.type timer_tick_asm, @function
timer_tick_asm:
	pushal
	call timer_tick_handler
	popal
	iret
