global isr0
global isr8
global isr13
global isr14

extern exception_common_handler

%macro ISR_NOERR 1
isr%1:
    push dword 0
    push dword %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERR 1
isr%1:
    push dword %1
    jmp isr_common_stub
%endmacro

ISR_NOERR 0 ; divide by zero
ISR_ERR 8 ; double fault
ISR_ERR 13 ; GPF
ISR_ERR 14 ; page fault

; common stub
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call exception_common_handler
    add esp, 4
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iretd
