#!/bin/bash

# why am I doing this manually..

set -e # stops on errors

mkdir -p build

# assemble asm files
find kernel/asm -name "*.asm" | while read -r file; do
    out="build/$(basename "${file%.*}").o"
    nasm -f elf32 "$file" -o "$out"
done

CFLAGS="-ffreestanding -m32 -fno-stack-protector -fno-rtti -fno-exceptions"

# assemble cpp files
find kernel -name "*.cpp" | while read -r file; do
    out="build/${file%.*}.o"
    mkdir -p "$(dirname "$out")"
    g++ $CFLAGS -c "$file" -o "$out"
done

# link everything
mapfile -t objs < <(find build -type f -name "*.o" | sort)
ld -m elf_i386 -n -T linker.ld -o build/kernel.elf "${objs[@]}"

# move the .elf
mv build/kernel.elf isodir/boot/kernel.elf

# recreate iso, overwrite old prayer.iso
grub-mkrescue -o prayer.iso isodir

echo "build complete"