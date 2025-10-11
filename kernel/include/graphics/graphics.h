#pragma once
#include <cstdint>

namespace graphics {
    extern uint32_t* framebuffer;
    extern uint32_t width;
    extern uint32_t height;
    extern uint32_t pitch;

    enum PixelColor : uint32_t {
        WHITE = 0xFFFFFFFF,
        BLACK  = 0xFF000000,
        YELLOW = 0xFFFFFF00,
        GRAY   = 0xFFAAAAAA,
        RED    = 0xFFFF0000,
        GREEN  = 0xFF00FF00,
        BLUE   = 0xFF0000FF,
    };

    void putp(uint32_t x, uint32_t y, PixelColor color);
    uint32_t getp(uint32_t x, uint32_t y);
    void clear(PixelColor color);

    void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, PixelColor color); // draw a simple rectangle
    void draw_cross(uint32_t center_x, uint32_t center_y, uint32_t size, PixelColor color); // draw a cross
    void boot_screen(); // draw the boot screen
}
