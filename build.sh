#!/bin/bash

set -e # stops on errors

mkdir -p build

# assemble asm files
nasm -f elf32 kernel/asm/gdt.asm -o build/gdt.o
nasm -f elf32 kernel/asm/boot.asm -o build/boot.o
nasm -f elf32 kernel/asm/inter_asm.asm -o build/inter_asm.o
nasm -f elf32 kernel/asm/exc_asm.asm -o build/exc_asm.o

# file compilation
g++ -ffreestanding -m32 -fno-stack-protector -c kernel/kmain.cpp -o build/kmain.o # kmain.cpp
g++ -ffreestanding -m32 -fno-stack-protector -c kernel/panic.cpp -o build/panic.o # panic.cpp
g++ -ffreestanding -m32 -fno-stack-protector -c kernel/vga.cpp -o build/vga.o # vga.cpp
g++ -ffreestanding -m32 -fno-stack-protector -c kernel/inter.cpp -o build/inter.o # inter.cpp
g++ -ffreestanding -m32 -fno-stack-protector -c kernel/exc.cpp -o build/exc.o # exc.cpp

# link everything
ld -m elf_i386 -n -T linker.ld -o build/kernel.elf build/gdt.o build/boot.o build/inter_asm.o build/exc_asm.o build/kmain.o build/panic.o build/vga.o build/inter.o build/exc.o

# move the .elf
mv build/kernel.elf isodir/boot/kernel.elf

# recreate iso, overwrite old prayer.iso
grub-mkrescue -o prayer.iso isodir

echo "build complete"