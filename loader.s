.text
.global loader
												# setting up the Multiboot loader = see GRUB docs for details
.set FLAGS, 0x0 								#this is the Multiboot 'flag' field.
.set MAGIC,  0x1BADB002 						#'magic number' lets bootloader find header - 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS) 				#=0xE4524FFE checksum required.

.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.set STACKSIZE, 0x4000 							#16k
.lcomm stack, STACKSIZE 						#reserve 16k stack
.comm mbd, 4  									#using this in kmain
.comm magic, 4 									#using this in kmain

loader:
	movl $(stack + STACKSIZE), %esp 			#set up the stack
	movl %eax, magic 							#Mulitboot magic number
	movl %ebx, mbd 								#Multiboot data structure
	cli
	call init_gdt
	call init_idt
	sti
	call main
	cli
hang:
	hlt
	jmp hang
