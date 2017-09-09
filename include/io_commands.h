#ifndef IO_COMMANDS_H
#define IO_COMMANDS_H

unsigned char inb(unsigned short);
void outb(unsigned short port, unsigned char val);
void io_wait();

#endif //IO_COMMANDS_H
