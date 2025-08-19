cmake_minimum_required(VERSION 3.15)

project(prayer_kernel LANGUAGES C CXX ASM_NASM)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(ASM_NASM)

file(GLOB_RECURSE KERNEL_SOURCES
        kernel/*.cpp
        kernel/*.c
        kernel/asm/*.asm
)

add_executable(prayer ${KERNEL_SOURCES})

target_compile_options(prayer PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-ffreestanding -fno-exceptions -fno-rtti -m32>
        $<$<COMPILE_LANGUAGE:ASM_NASM>:-f elf32>
)

target_link_options(prayer PRIVATE
        -T${CMAKE_SOURCE_DIR}/linker.ld
        -nostdlib
        -e kmain
)

add_custom_target(iso ALL
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/prayer ${CMAKE_SOURCE_DIR}/isodir/boot/kernel.elf
        COMMAND grub-mkrescue -o ${CMAKE_SOURCE_DIR}/prayer.iso ${CMAKE_SOURCE_DIR}/isodir
        DEPENDS prayer
)

