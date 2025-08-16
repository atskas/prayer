#pragma once
#include <cstdint>

#include "color.h"

extern volatile uint16_t* vga_base;

// Override the VGA base
void vga_override(void* new_base);

// Initiate the VGA buffer
void vga_init();

// Update the blinking cursor's position
void vga_update_cursor();

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
void vga_set_color(Color fg, Color bg);

