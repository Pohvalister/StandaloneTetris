#ifndef IO_COMMANDS_H
#define IO_COMMANDS_H

#include "types.h"

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);

#endif //IO_COMMANDS_H
