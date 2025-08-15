#include "../kernel/include/exc.h"
#include "../kernel/include/inter.h"
#include "include/vga.h"

// Sets IDT entries
void exc_init() {
    set_idt_entry(0, (uint32_t)isr0, 0x08, 0x8E);
    set_idt_entry(8, (uint32_t)isr8, 0x08, 0x8E);
    set_idt_entry(13, (uint32_t)isr13, 0x08, 0x8E);
    set_idt_entry(14, (uint32_t)isr14, 0x08, 0x8E);
}

extern "C" void exception_common_handler(int vector, uint32_t error_code, regs_t *regs) {
    vga_print("Exception occured!\n");

    vga_print("int_no: "); vga_print_hex(regs->int_no); vga_print("\n");
    vga_print("err_code: "); vga_print_hex(regs->err_code); vga_print("\n");

    vga_print("EAX: "); vga_print_hex(regs->eax); vga_print("\n");
    vga_print("EBX: "); vga_print_hex(regs->ebx); vga_print("\n");
    while (1) { asm volatile("hlt"); }
}
