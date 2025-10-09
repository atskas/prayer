#pragma once
#include <cstdint>

namespace graphics {
    inline uint32_t* framebuffer = nullptr;
    inline uint32_t width = 0;
    inline uint32_t height = 0;
    inline uint32_t pitch = 0;

    void putp(uint32_t x, uint32_t y, uint32_t color);
    void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
}
