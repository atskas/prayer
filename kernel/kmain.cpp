#include "include/exc.h"
#include "include/vga.h"
#include "include/inter.h"
#include "include/pag.h"

// Entry point
extern "C" void kstart() {
    vga_init();
    exc_init();
    idt_init();
    paging_init();

    // Map an unused virtual address to the physical VGA memory
    uint32_t virt_vga = 0x400000;
    map_page(virt_vga, 0xB8000, 0x3 | 0x8);

    // Override the VGA base address with the virtual address
    vga_override((void*)virt_vga);

    // Print to the address
    vga_print("Hello World!");


    while(true) asm volatile("hlt");
}