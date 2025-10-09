#include "include/exc.h"
#include "include/vga.h"
#include "include/inter.h"
#include "include/pag.h"
#include "include/time.h"
#include "include/graphics/graphics.h"

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
            graphics::framebuffer = (uint32_t*)tag->framebuffer.addr;
            graphics::pitch = tag->framebuffer.pitch;
            graphics::width = tag->framebuffer.width;
            graphics::height = tag->framebuffer.height;
            break;
        }
        tag = (multiboot2_tag*)((uint8_t*)tag + ((tag->size + 7) & ~7));
    }

    graphics::putp(0, 0, 0xFFFFFFFF);
    graphics::draw_rect(50, 50, 50, 50, 0xFFFFFFFF);

    exc_init();
    idt_init();
    paging_init();
    pit_init(100);

    while(true) asm volatile("hlt");
}