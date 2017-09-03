#include "pic.h"

struct gate {
	unsigned short offset_1;
	unsigned short segment_selector;
	unsigned char reserved;
	unsigned char flags;
	unsigned short offset_2;
} __attribute__((packed));

struct gate idt[256];

extern void key_pressed_handler_asm();
extern void timer_tick_handler_asm();

void init_gate(void* function_addr, int interrupt_id) {
	unsigned int fa = (unsigned int) function_addr;
	idt[interrupt_id].offset_1 = fa & 0xffff;
	idt[interrupt_id].segment_selector = 0x10;
	idt[interrupt_id].reserved = 0;
	idt[interrupt_id].flags = (0xe) | (1 << 7);
	idt[interrupt_id].offset_2 = (unsigned short) (fa >> 16);
}

struct idtr_t {
	unsigned short size;
	unsigned int addr;
} __attribute__((packed));

void load_idt(unsigned short sz, struct gate *idt_addr) {
	struct idtr_t idtr;
	idtr.size = sz - 1;
	idtr.addr = (unsigned int) idt_addr;
	asm ("lidt (%0)": : "a"(&idtr) : "memory" );
}

void init_idt() {
	PIC_remap(PIC1, PIC2);
	init_gate((void*)&key_pressed_handler_asm, PIC_OFFSET + 1);
	init_gate((void*)&timer_tick_handler_asm, PIC_OFFSET);
	load_idt(sizeof(idt), idt);
}
