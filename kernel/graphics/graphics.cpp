#include "../include/graphics/graphics.h"

#include "../include/time.h"

namespace graphics {
    uint32_t* framebuffer = nullptr;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t pitch = 0;

    void putp(uint32_t x, uint32_t y, PixelColor color) {
        if (!framebuffer) return;
        if (x >= width || y >= height) return; // check so as not to write past framebuffer
        uint8_t* fb = (uint8_t*)framebuffer;
        uint8_t* pixel = fb + y * pitch + x * 4;
        *(uint32_t*)pixel = color;
    }

    uint32_t getp(uint32_t x, uint32_t y) {
        if (!framebuffer) return 0;

        uint8_t* fb = (uint8_t*)framebuffer;
        uint8_t* pixel = fb + y * pitch + x * 4;
        return *(uint32_t*)pixel;
    }

    void clear(PixelColor color) {
        if (!framebuffer) return;

        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {
                putp(x, y, color);
            }
        }
    }

    void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, PixelColor color) {
        for (uint32_t j = 0; j < h; j++) {
            for (uint32_t i = 0; i < w; i++) {
                putp(x + i, y + j, color);
            }
        }
    }

    void draw_cross(uint32_t center_x, uint32_t center_y, uint32_t size, PixelColor color) {
        uint32_t half = size / 2;

        // vertical line
        draw_rect(center_x - 6, center_y - half, 7, size, color);

        // horizontal line
        draw_rect(center_x - half, center_y - 8, size - 8, 7, color);
    }

    void boot_screen() {
        uint32_t center_x = width / 2;
        uint32_t center_y = height / 2;

        clear(BLACK);
        draw_cross(center_x, center_y, 48, WHITE);

        wait_ms(2000);
        clear(BLACK);
    }


}
