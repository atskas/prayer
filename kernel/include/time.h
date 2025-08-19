#pragma once
#include <cstdint>

// The total number of PIT interrupts since boot.
extern volatile uint32_t ticks;

// Set the PIT to fire IRQ0 at a given frequency
void pit_init(uint32_t frequency);
extern "C" void pit_tick();

uint32_t ms_since_boot(); // Uptime in milliseconds.
uint32_t s_since_boot(); // Uptime in seconds.

void wait_ms(uint32_t ms); // Halt the cpu for a specified amount of time in milliseconds.