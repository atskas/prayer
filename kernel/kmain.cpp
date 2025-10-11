#include "include/exc.h"
#include "include/vga.h"
#include "include/inter.h"
#include "include/time.h"
#include "include/graphics/graphics.h"
#include "include/graphics/ui/gui.h"
#include "include/graphics/ui/widget.h"
#include "include/input/mouse.h"

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

    exc_init();
    idt_init();
    pit_init(100);

    graphics::boot_screen();

    // test button
    Widget* tb = gui::create_widget(graphics::width / 2, graphics::height / 2, 120, 40);

    // test button color handling
    tb->on_update = [](Widget* w){
        if(w->pressed)
            w->color = graphics::YELLOW;
        else if(w->hovered)
            w->color = graphics::GRAY;
        else
            w->color = graphics::WHITE;
    };

    // draw the rectangle with the properties
    tb->draw = [](Widget* w) {
        graphics::draw_rect(w->x, w->y, w->w, w->h, w->color);
    };

    while (true) {
        // ui draw loop
        gui::update(mouse::cursor_x, mouse::cursor_y, mouse::mouse_button_pressed(LEFT));
        gui::draw();
        mouse::draw_cursor(); // draw the cursor
    }

    while(true) asm volatile("hlt");
}