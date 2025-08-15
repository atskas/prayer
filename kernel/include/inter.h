#pragma once
#include <cstdint>
#include <bits/stdint-uintn.h>

void idt_init();

void set_idt_entry(int vector, uint32_t handler, uint16_t selector, uint8_t type_attr);

struct __attribute__((packed)) IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
};

struct __attribute__((packed)) IDTPtr {
    uint16_t limit; // Size of the table - 1
    uint32_t base; // Address of the first entry
};
