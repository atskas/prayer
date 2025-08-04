#include "include/panic.h"

// This function is called on panic.
[[noreturn]] void panic(const char* info) {
    asm volatile("cli");
    while (true)
        asm volatile("hlt");
}