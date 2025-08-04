cmake_minimum_required(VERSION 3.15)

project(prayer_kernel LANGUAGES C CXX ASM_NASM)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(ASM_NASM)

set(SOURCES
        kernel/asm/boot.asm
        kernel/kmain.cpp
        linker.ld
        kernel/include/panic.h
        kernel/panic.cpp
        kernel/vga/vga_buffer.cpp
        kernel/include/vga_buffer.h
        kernel/include/vga_color.h
)

add_executable(prayer ${SOURCES})

target_compile_options(prayer PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-ffreestanding -fno-exceptions -fno-rtti -m64>
        $<$<COMPILE_LANGUAGE:ASM_NASM>:-f elf64>
)

target_link_options(prayer PRIVATE
        -T${CMAKE_SOURCE_DIR}/linker.ld
        -nostdlib
        -e _start
)
