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

    while(true) asm volatile("hlt");
}