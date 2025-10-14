#include "include/exc.h"
#include "include/inter.h"
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
            graphics::hardware_framebuffer = (uint32_t*)tag->framebuffer.addr;
            graphics::framebuffer = graphics::backbuffer;
            graphics::pitch = tag->framebuffer.pitch;
            graphics::width = tag->framebuffer.width;
            graphics::height = tag->framebuffer.height;
            break;
        }
        tag = (multiboot2_tag*)((uint8_t*)tag + ((tag->size + 7) & ~7));
    }

    exc_init();
    idt_init();
    asm volatile("sti"); // Enable global interrupts

    graphics::boot_screen();

    uint32_t taskbar_y = graphics::height - 30;
    uint32_t taskbar_height = 30;

    Widget* taskbar = gui::create_widget(0, taskbar_y, graphics::width, taskbar_height);
    taskbar->z_index = 100;
    taskbar->draw = [](Widget* w) {
        graphics::draw_rect(w->x, w->y, w->w, w->h, graphics::YELLOW);
    };

    Widget* box = gui::create_widget(0, taskbar_y, 25, taskbar_height);
    box->z_index = 101;
    box->on_update = [](Widget* w) {
        static bool was_pressed = false;
        if (w->pressed && !was_pressed) {
            w->color = graphics::GREEN;
        } else if (w->hovered) {
            w->color = graphics::GRAY;
        } else {
            w->color = graphics::RED;
        }
    };
    box->draw = [](Widget* w) {
        graphics::draw_rect(w->x, w->y, w->w, w->h, w->color);
    };

    Widget* rectangle = gui::create_widget(100, 100, 100, 80);
    rectangle->z_index = 0;
    rectangle->on_update = [](Widget* w) {
        if (w->pressed) {
            w->x = mouse::cursor_x - 20;
            w->y = mouse::cursor_y - 20;
        }
        w->color = graphics::GREEN;
    };
    rectangle->draw = [](Widget* w) {
        graphics::draw_rect(w->x, w->y, w->w, w->h, w->color);
    };

    while (true) {
        graphics::framebuffer = graphics::backbuffer;
        graphics::clear(graphics::BLUE);
        gui::update(mouse::cursor_x, mouse::cursor_y, mouse::mouse_button_pressed(LEFT));
        gui::draw();
        mouse::draw_cursor(mouse::cursor_x, mouse::cursor_y); // draw the cursor

        graphics::swap_buffers();
    }

    while(true) asm volatile("hlt");
}