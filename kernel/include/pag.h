#pragma once
#include <cstdint>

void paging_init();

// Functions defined in the .asm
extern "C" void load_page_directory(uint32_t);
extern "C" void enable_paging();

void map_page(uint32_t virt, uint32_t phys, uint32_t flags);

void unmap_page(uint32_t virt);