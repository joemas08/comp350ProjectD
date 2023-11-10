#!/bin/bash

: '
Joseph Masone
Natalio Gomes
COMP350-001
November 2, 2023
'

dd if=/dev/zero of=diskc.img bs=512 count=256
nasm bootload.asm
dd if=bootload of=diskc.img conv=notrunc
bcc -ansi -c -o kernel_c.o kernel.c
bcc -ansi -c -o tstpr1.o tstpr1.c
as86 kernel.asm -o kernel_asm.o
as86 -o userlib.o userlib.asm
ld86 -o kernel -d kernel_c.o kernel_asm.o
ld86 -d -o tstpr1 tstpr1.o userlib.o
./loadFile kernel
./loadFile message.txt 
./loadFile tstpr1
