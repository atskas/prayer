#include "../include/graphics/graphics.h"

#include "../include/time.h"

namespace graphics {
    uint32_t* framebuffer = nullptr;
    uint32_t* hardware_framebuffer = nullptr;
    uint32_t backbuffer_storage[MAX_FB_SIZE];
    uint32_t* backbuffer = backbuffer_storage;
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
        if (x >= width || y >= height) return 0;

        uint8_t* fb = (uint8_t*)framebuffer;
        uint8_t* pixel = fb + y * pitch + x * 4;
        return *(uint32_t*)pixel;
    }

    void clear(PixelColor color) {
        if (!framebuffer) return;

        uint32_t stride = pitch / 4; // pixels per row in memory
        for (uint32_t y = 0; y < height; y++) {
            uint32_t row_start = y * stride;
            uint32_t max_x = width;
            if (row_start + width > MAX_FB_SIZE) max_x = MAX_FB_SIZE - row_start;

            for (uint32_t x = 0; x < max_x; x++) {
                backbuffer[row_start + x] = color;
            }
        }
    }

    void swap_buffers() {
        if (!hardware_framebuffer || !backbuffer) return;

        uint32_t stride = pitch / 4;
        for (uint32_t y = 0; y < height; y++) {
            uint32_t row_start = y * stride;
            uint32_t max_x = width;
            if (row_start + width > MAX_FB_SIZE) max_x = MAX_FB_SIZE - row_start;

            for (uint32_t x = 0; x < max_x; x++) {
                hardware_framebuffer[row_start + x] = backbuffer[row_start + x];
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

        swap_buffers();
        wait_ms(2000);

        clear(BLACK);
        swap_buffers();
    }
}
