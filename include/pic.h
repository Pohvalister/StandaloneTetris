#ifndef PIC_H
#define PIC_H

#define PIC1		0x20
#define PIC2		0xA0
#define PIC_OFFSET 	0x20

void PIC_sendEOI(unsigned char irq);
void PIC_remap(int offset1, int offset2);

#endif //PIC_H
