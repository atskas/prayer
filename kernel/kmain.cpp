#include "include/exc.h"
#include "include/vga.h"
#include "include/inter.h"
#include "include/pag.h"
#include "include/time.h"

// Temporarily held here (probably)
struct multiboot2_tag {
    uint32_t type;
    uint32_t size;
    union {
        struct {
            uint64_t addr;
            uint32_t pitch;
            uint32_t width;
            uint32_t height;
            uint8_t bpp;
            uint8_t reserved[3];
        } framebuffer;
    };
};


// Entry point
extern "C" void kstart(void* mb_info) {
    auto* tag = (multiboot2_tag*)((uint8_t*)mb_info + 8);
    while(tag->type != 0) {
        if(tag->type == 8) {
            uint32_t* fb = (uint32_t*)tag->framebuffer.addr;
            fb[0] = 0xFFFF00FF;
            break;
        }
        tag = (multiboot2_tag*)((uint8_t*)tag + ((tag->size + 7) & ~7));
    }

    exc_init();
    idt_init();
    paging_init();
    pit_init(100);

    while(true) asm volatile("hlt");
}