#include "pic.h"

struct gate {
	unsigned short offset_1;
	unsigned short segment_selector;
	unsigned char reserved;
	unsigned char flags;
	unsigned short offset_2;
} __attribute__((packed));

struct gate idt[256];

void key_pressed_asm();
void timer_tick_asm();

void init_gate(void* function_addr, int interrapt_id) {
	unsigned int fa = (unsigned int) function_addr;
	idt[interrapt_id].offset_1 = fa & 0xffff;
	idt[interrapt_id].segment_selector = 0x10;
	idt[interrapt_id].reserved = 0;
	idt[interrapt_id].flags = (0xe) | (1 << 7);
	idt[interrapt_id].offset_2 = (unsigned short) (fa >> 16);
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
	pic_remap(PIC1, PIC2);
	init_gate((void*)&key_pressed_asm, PIC_OFFSET + 1);
	init_gate((void*)&timer_tick_asm, PIC_OFFSET);
	load_idt(sizeof(idt), idt);
}
