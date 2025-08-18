#include "time.h"
#include "../kernel/include/helper.h"

volatile uint32_t ticks = 0;
static uint32_t pit_frequency;

extern "C" void pit_tick() {
    ticks++;
}

void pit_init(uint32_t frequency) {
    pit_frequency = frequency;

    uint16_t divisor = 1193182 / frequency;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}

// Uptime in milliseconds
uint32_t ms_since_boot() {
    return ticks * 1000 / pit_frequency;
}

// Uptime in seconds
uint32_t s_since_boot() {
    return ticks / pit_frequency;
}