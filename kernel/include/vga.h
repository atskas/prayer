#pragma once
#include <cstdint>

extern volatile uint16_t* vga_base;

// Enum for simplified text mode color use.
enum VGAColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GRAY = 7,
    DARK_GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15,
};

// Override the VGA base
void vga_override(void* new_base);

// Initiate the VGA buffer
void vga_init();

// Update the blinking cursor's position
void vga_update_cursor();

// Shift all lines up.
void vga_scroll();

// Print text to the screen
void vga_print(const char* str);

// For printing a char.
void vga_printc(char c);

// Goes back a character
void vga_back();

// Print hex
void vga_print_hex(uint32_t val);

// Move where the next print will start writing
void vga_set_cursor(int row, int col);

// Clear screen
void vga_clear();

// Set the text color
void vga_set_color(VGAColor fg, VGAColor bg);

