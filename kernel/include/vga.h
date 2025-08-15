#pragma once
#include <cstdint>

#include "color.h"

// Initiate the VGA buffer
void vga_init();

// Print text to the screen
void vga_print(const char* str);

// Print hex
void vga_print_hex(uint32_t val);

// Move where the next print will start writing
void vga_set_cursor(int row, int col);

// Clear screen
void vga_clear();

// Set the text color
void vga_set_color(Color fg, Color bg);

