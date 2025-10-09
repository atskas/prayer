#include "../include/graphics/graphics.h"

namespace graphics {
    void putp(uint32_t x, uint32_t y, uint32_t color) {
        if(!framebuffer) return;

        uint8_t* fb = (uint8_t*)framebuffer;

        uint8_t* pixel = fb + y * pitch + x * 4;
        *(uint32_t*)pixel = color;
    }

    void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
        for (uint32_t j = 0; j < h; j++) {
            for (uint32_t i = 0; i < w; i++) {
                putp(x + i, y + j, color);
            }
        }
    }
}