#!/bin/bash

set -e # stops on errors

mkdir -p build

# assemble boot.asm
nasm -f elf32 kernel/asm/boot.asm -o build/boot.o

# file compilation
g++ -ffreestanding -m32 -c kernel/kmain.cpp -o build/kmain.o # kmain.cpp
g++ -ffreestanding -m32 -c kernel/panic.cpp -o build/panic.o # panic.cpp


# link everything
ld -m elf_i386 -n -T linker.ld -o build/kernel.elf build/boot.o build/kmain.o build/panic.o

# move the .elf
mv build/kernel.elf isodir/boot/kernel.elf

# recreate iso, overwrite old prayer.iso
grub-mkrescue -o prayer.iso isodir

echo "build complete"