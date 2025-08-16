#include "../kernel/include/pag.h"

alignas(4096) uint32_t page_directory[1024];
alignas(4096) uint32_t first_page_table[1024];

void paging_init() {
    for (uint32_t i = 0; i < 1024; i++)
        first_page_table[i] = i * 0x1000 | 0x3;

    // Point first page directory entry to first table
    page_directory[0] = (uint32_t)first_page_table | 0x3;

    load_page_directory((uint32_t)page_directory);
    enable_paging();
}