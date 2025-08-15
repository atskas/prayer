[BITS 32]
global load_gdt

gdt_start:
    dq 0x0000000000000000     ; null descriptor

    ; Kernel code segment: base=0, limit=4GB, execute/read, ring 0
    dq 0x00CF9A000000FFFF

    ; Kernel data segment: base=0, limit=4GB, read/write, ring 0
    dq 0x00CF92000000FFFF

gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start - 1   ; size
    dd gdt_start                 ; address

load_gdt:
    lgdt [gdt_ptr]

    mov ax, 0x10        ; 0x10 = kernel data selector (3rd entry)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Reload CS with kernel code selector
    jmp 0x08:flush_cs

flush_cs:
    ret
