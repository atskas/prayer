section .text
global _start
extern kstart

_start:
    call kstart

.hang:
    hlt
    jmp .hang

; GRUB requires the multiboot2 header to be within first 32 KiB
section .multiboot2
align 8

    dd 0xe85250d6           ; magic number
    dd 0                    ; architecture = i386
    dd header_end - header  ; header length
    dd 0 - (0xe85250d6 + 0 + (header_end - header))  ; checksum

header:
    dw 0        ; type = 0 (end tag)
    dw 0        ; flags
    dd 8        ; size
header_end:
