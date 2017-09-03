#линковщик использует loader как точку входа
#Код на ассемблере, который вызывается Grub’ом и передает управление функции main из программы	на С
.text
.global loader
												# setting up the Multiboot loader = see GRUB docs for details
.set FLAGS, 0x0 								#this is the Multiboot 'flag' field. Флаги, которые содержат дополнительные требования к загрузке ядра и параметрам, передаваемым загрузчиком ядру (нашей программе). В данном случае все флаги сброшены.
.set MAGIC,  0x1BADB002 						#'magic number' lets bootloader find header - 0x1BADB002 Сигнатура формата Multiboot
.set CHECKSUM, -(MAGIC + FLAGS) 				#=0xE4524FFE checksum required. - Контрольная сумма.

.align 4										#выровнять следующие данные по 4 байта
.long MAGIC 									#long сохраняет значения в 4 х последующих байтах
.long FLAGS
.long CHECKSUM

.set STACKSIZE, 0x4000 							#16k
.lcomm stack, STACKSIZE 						#reserve 16k stack, зарезервировали - теперь stack сслается на диапазон, stack - будет виден только в компилируемом файле
.comm mbd, 4  									#using this in kmain - 4 байта под переменную mbd в области COMMON
.comm magic, 4 									#using this in kmain

loader:
	movl $(stack + STACKSIZE), %esp 			#set up the stack
	movl %eax, magic 							#Mulitboot magic number
	movl %ebx, mbd 								#Multiboot data structure
	
	cli
	call init_gdt
	call init_idt
	sti

	call main 									#call C code -функцию main	
	cli 										# отключить прерывания от оборудования
hang:
	hlt 										#halt machine should kernel return - остановить процессор пока не возникнет прерывание
	jmp hang 									# прыгнуть на метку hang


