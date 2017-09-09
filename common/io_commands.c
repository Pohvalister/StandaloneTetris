#include "io_commands.h"

unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb(unsigned short port, unsigned char val) {
    asm ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void io_wait() {
    asm ( "outb %%al, $0x80" : : "a"(0) );
}
