#include "../kernel/include/vga.h"
#include "../kernel/include/keys.h"
#include <cstdint>

static volatile uint16_t* vga_buffer;
static int cursor_row = 0;
static int cursor_col = 0;
static Color fg_color;
static Color bg_color;

// Sets the background & foreground color
void vga_set_color(Color fg, Color bg) {
    fg_color = fg;
    bg_color = bg;
}

// Initialise the VGA buffer and all other properties
void vga_init() {
    vga_buffer = (uint16_t*)0xB8000;
    cursor_row = 0;
    cursor_col = 0;
    vga_set_color(WHITE, BLACK);
}

// Print text to the screen
void vga_print(const char* str) {
    uint8_t color_byte = (bg_color << 4) | fg_color;

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '\n') {
            cursor_col = 0;
            cursor_row++;
            if (cursor_row >= 25) {
                cursor_row = 24; // Temporarily clamp
            }
            continue;
        }

        uint16_t value = (color_byte << 8) | c;
        vga_buffer[cursor_row * 80 + cursor_col] = value;

        cursor_col++;
        if (cursor_col >= 80) {
            cursor_col = 0;
            cursor_row++;
            if (cursor_row >= 25) {
                cursor_row = 24; // Temporarily clamp
            }
        }
    }
}

// For printing hex codes
void vga_print_hex(uint32_t val) {
    const char* hex = "0123456789ABCDEF";
    vga_print("0x");
    char buf[2] = {0, 0};
    for (int i = 28; i >= 0; i -= 4) {
        buf[0] = hex[(val >> i) & 0xF];
        vga_print(buf);
    }
}

extern "C" const char* scancode_to_key(uint8_t scancode, bool* released) {
    *released = scancode & 0x80;
    uint8_t code = scancode & 0x7F;
    if (code < 128) return scancode_table[code];
    return "UNKNOWN";
}


