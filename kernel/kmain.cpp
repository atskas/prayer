#include "include/exc.h"
#include "include/vga.h"
#include "include/panic.h"
#include "include/inter.h"

// Entry point
extern "C" void kstart() {
    vga_init();
    vga_print("Hello World!\n");
    exc_init();
    idt_init();

    while(true) asm volatile("hlt");
}