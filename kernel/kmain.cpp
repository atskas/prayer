#include "include/exc.h"
#include "include/vga.h"
#include "include/inter.h"
#include "include/pag.h"
#include "include/time.h"
#include "include/shell/shell.h"

// Entry point
extern "C" void kstart() {
    vga_init();
    exc_init();
    idt_init();
    paging_init();
    pit_init(100);

    shell_loop();

    while(true) asm volatile("hlt");
}