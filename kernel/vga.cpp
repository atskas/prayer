#include "../kernel/include/vga.h"
#include "../kernel/include/keys.h"
#include <cstdint>

#include "include/io.h"

volatile uint16_t* vga_base;
static int cursor_row = 0;
static int cursor_col = 0;
static Color fg_color;
static Color bg_color;

// Override the VGA base
void vga_override(void* new_base) {
    vga_base = (volatile uint16_t*)new_base;
}

// Initialise the VGA buffer and all other properties
void vga_init() {
    vga_base = (uint16_t*)0xB8000;
    cursor_row = 0;
    cursor_col = 0;
    vga_set_color(WHITE, BLACK);
}

void vga_update_cursor() {
    const uint16_t pos = cursor_row * 80 + cursor_col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, pos & 0xFF);
    outb(0x3D4, 0x0E);
    outb(0x3D5, (pos >> 8) & 0xFF);
}

// Sets the background and foreground color
void vga_set_color(Color fg, Color bg) {
    fg_color = fg;
    bg_color = bg;
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
            vga_update_cursor();
            continue;
        }

        uint16_t value = (color_byte << 8) | c;
        vga_base[cursor_row * 80 + cursor_col] = value;

        cursor_col++;
        if (cursor_col >= 80) {
            cursor_col = 0;
            cursor_row++;
            if (cursor_row >= 25) {
                cursor_row = 24; // Temporarily clamp
            }
        }
        vga_update_cursor();
    }
}

// For printing a char
void vga_printc(char c) {
    uint8_t color_byte = (bg_color << 4) | fg_color;

    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= 25) cursor_row = 24;
        vga_update_cursor();
        return;
    }

    uint16_t value = (color_byte << 8) | c;
    vga_base[cursor_row * 80 + cursor_col] = value;

    cursor_col++;
    if (cursor_col >= 80) {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= 25) cursor_row = 24;
    }
    vga_update_cursor();
}

// Mainly for handling backspace, goes back a character.
void vga_back() {
    if (cursor_col > 0) {
        cursor_col--;
    } else if (cursor_row > 0) {
        cursor_row--;
        cursor_col = 79;
    } else {
        return;
    }

    uint16_t color_byte = (bg_color << 4) | fg_color;
    vga_base[cursor_row * 80 + cursor_col] = (color_byte << 8) | ' ';
    vga_update_cursor();
}

// To print hex codes
void vga_print_hex(uint32_t val) {
    const char* hex = "0123456789ABCDEF";
    vga_print("0x");
    char buf[2] = {0, 0};
    for (int i = 28; i >= 0; i -= 4) {
        buf[0] = hex[(val >> i) & 0xF];
        vga_print(buf);
    }
}


