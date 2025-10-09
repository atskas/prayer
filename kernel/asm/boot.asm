section .text
global _start
extern kstart
extern load_gdt

_start:
    cli ; disable interrupts
    mov esp, 0x00104000 ; 1MB + 16 KB stack
    call load_gdt
    push ebx
    call kstart
    add esp, 4
    hlt ; for safety

.hang:
    hlt
    jmp .hang

; GRUB requires the multiboot2 header to be within first 32 KiB
section .multiboot2
align 8

    dd 0xe85250d6 ; magic number
    dd 0 ; architecture = i386
    dd header_end - header ; header length
    dd 0 - (0xe85250d6 + 0 + (header_end - header)) ; checksum

header:
    ; framebuffer tag
    dw 5 ; type
    dw 1 ; flags
    dd 24 ; size
    dd 640 ; width
    dd 480 ; height
    dd 32 ; bpp
    dd 0

    ; end tag
    dw 0
    dw 0
    dd 8
header_end:
