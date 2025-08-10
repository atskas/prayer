#include <cstdint>
#include <cstddef>
#include "include/vga.h"
#include "include/panic.h"

// Entry point
extern "C" void kstart() {
    vga_init();
    vga_print("Hello World!");
}