#include <cstdint>
#include <cstddef>
#include "include/panic.h"

// This is the kernel's entry point.
extern "C" void kstart() {
    const char* hello = "Hello World!";

    volatile uint8_t* vga = (uint8_t*) 0xb8000;
    for (size_t i = 0; hello[i] != '\0'; ++i) {
        vga[i * 2] = hello[i]; // character
        vga[i * 2 + 1] = 0x0B; // light cyan color
    }

    panic("something went wrong");
}