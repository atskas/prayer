#!/bin/bash

# why am I doing this manually..

set -e # stops on errors

mkdir -p build
mkdir -p build/shell
mkdir -p build/shell/commands

# assemble asm files
nasm -f elf32 kernel/asm/gdt.asm -o build/gdt.o
nasm -f elf32 kernel/asm/boot.asm -o build/boot.o
nasm -f elf32 kernel/asm/inter_asm.asm -o build/inter_asm.o
nasm -f elf32 kernel/asm/exc_asm.asm -o build/exc_asm.o
nasm -f elf32 kernel/asm/pag_asm.asm -o build/pag_asm.o

# file compilation
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/kmain.cpp -o build/kmain.o # kmain.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/panic.cpp -o build/panic.o # panic.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/vga.cpp -o build/vga.o # vga.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/inter.cpp -o build/inter.o # inter.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/exc.cpp -o build/exc.o # exc.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/keyboard.cpp -o build/keyboard.o # keyboard.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/pag.cpp -o build/pag.o # pag.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/shell.cpp -o build/shell/shell.o # shell.cpp
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/time.cpp -o build/time.o # time.cpp

# commands
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/commands/echo.cpp -o build/shell/commands/echo.o
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/commands/banner.cpp -o build/shell/commands/banner.o
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/commands/clear.cpp -o build/shell/commands/clear.o
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/commands/color.cpp -o build/shell/commands/color.o
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/commands/help.cpp -o build/shell/commands/help.o
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/commands/fillc.cpp -o build/shell/commands/fillc.o
g++ -ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions -c kernel/shell/commands/uptime.cpp -o build/shell/commands/uptime.o

# link everything
ld -m elf_i386 -n -T linker.ld -o build/kernel.elf build/gdt.o build/boot.o build/inter_asm.o build/exc_asm.o build/pag_asm.o build/kmain.o build/panic.o build/vga.o build/inter.o build/exc.o build/keyboard.o build/pag.o build/shell/shell.o build/shell/commands/echo.o build/shell/commands/banner.o build/shell/commands/clear.o build/shell/commands/color.o build/shell/commands/help.o build/shell/commands/fillc.o build/time.o build/shell/commands/uptime.o

# move the .elf
mv build/kernel.elf isodir/boot/kernel.elf

# recreate iso, overwrite old prayer.iso
grub-mkrescue -o prayer.iso isodir

echo "build complete"