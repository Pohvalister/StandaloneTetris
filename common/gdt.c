struct segment_descriptor_t { 
	unsigned short segment_limit_1;
	unsigned short base_address_1;
	unsigned char base_address_2;
	unsigned char type_and_flags;
	unsigned char segment_limit_2_and_flags;
	unsigned char base_address_3;
};

struct segment_descriptor_t gdt[3];

void init_null_sd() {
	gdt[0].segment_limit_1 = 0;
	gdt[0].base_address_1 = 0;
	gdt[0].base_address_2 = 0;
	gdt[0].type_and_flags = 0;
	gdt[0].segment_limit_2_and_flags = 0;
	gdt[0].base_address_3 = 0;
}

void init_data_sd()  {
	gdt[1].segment_limit_1 = 0xffff;
	gdt[1].base_address_1 = 0;
	gdt[1].base_address_2 = 0;
	gdt[1].type_and_flags = (1 << 1) | (1 << 4) | (1 << 7);
	gdt[1].segment_limit_2_and_flags = (0xff) | (1 << 6) | (1 << 7);
	gdt[1].base_address_3 = 0;
}

void init_code_sd()  {
	gdt[2].segment_limit_1 = 0xffff;
	gdt[2].base_address_1 = 0;
	gdt[2].base_address_2 = 0;
	gdt[2].type_and_flags = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 7);
	gdt[2].segment_limit_2_and_flags = (0xff) | (1 << 6) | (1 << 7);
	gdt[2].base_address_3 = 0;	
}

struct gdtr_t {
    unsigned short size;
    unsigned int addr;
} __attribute__((packed)) ;

void load_gdt(struct segment_descriptor_t *gdt_ptr, unsigned short sz) {
	struct gdtr_t gdtr;
	gdtr.size = sz - 1;
	gdtr.addr = (unsigned int) gdt_ptr;
  	asm ("lgdt (%0)": : "a"(&gdtr));
  	asm("ljmp $0x10, $reload_cs\n\t"
	"reload_cs:\n\t"
	"mov $0x8, %%ax\n\t"
	"mov %%ax, %%ds\n\t"
	:
	:
	: "ax");
}

void init_gdt() {
	init_null_sd();
	init_data_sd();
	init_code_sd(); 
	load_gdt(gdt, sizeof(gdt));
}
