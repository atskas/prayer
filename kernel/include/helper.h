#pragma once
#include <stdint.h>

// Helper file

// Input byte
static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

// Output byte
static inline void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// String equal
static inline bool streq(const char* a, const char* b) {
    while (*a && *b) {
        if (*a++ != *b++) return false;
    }
    return *a == *b;
}

// String to integer
static inline int stoi(const char* str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c < '0' || c > '9') break;
        result = result * 10 + (c - '0');
    }
    return result;
}
