bits 32

global irq1_stub
global irq0_stub
global load_idt

extern irq0_handler
extern irq1_handler

; IRQ0 stub (timer)
irq0_stub:
    pusha
    call irq0_handler
    popa
    mov al, 0x20
    out 0x20, al
    iretd


; IRQ1 stub (keyboard)
irq1_stub:
    pusha
    call irq1_handler
    popa
    mov al, 0x20
    out 0x20, al
    iretd

; load_idt, called from C++ with pointer to IDTPtr
load_idt:
    mov eax, [esp+4] ; get pointer to IDTPtr
    lidt [eax] ; load it into CPU's IDTR
    ret
