#pragma once
#include <cstdint>

namespace graphics {
    extern uint32_t* framebuffer;
    extern uint32_t width;
    extern uint32_t height;
    extern uint32_t pitch;

    void putp(uint32_t x, uint32_t y, uint32_t color);
    void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
}
