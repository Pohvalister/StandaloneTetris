.globl   key_pressed_handler_asm
.align   4
 
key_pressed_handler_asm:
    pushal
    call key_pressed_handler
    popal
    iret

.globl   timer_tick_handler_asm
.align   4
 
timer_tick_handler_asm:
    pushal
    call timer_tick_handler
    popal
    iret
