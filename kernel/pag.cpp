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

void map_page(uint32_t virt, uint32_t phys, uint32_t flags) {
    uint32_t pd_index = virt >> 22;            // Top 10 bits
    uint32_t pt_index = (virt >> 12) & 0x3ff;  // Next 10 bits

    // If no page table exists for this directory entry, then create one
    if (!(page_directory[pd_index] & 0x1)) {
        // Simple static allocator
        static uint32_t next_free_table = 0;
        static uint32_t extra_page_tables[4][1024] __attribute__((aligned(4096)));

        uint32_t* new_table = extra_page_tables[next_free_table++];
        for (int i = 0; i < 1024; i++) new_table[i] = 0; // Clear it

        page_directory[pd_index] = ((uint32_t)new_table) | 0x3;
    }

    // Find the correct page table and set the entry
    uint32_t* page_table = (uint32_t*)(page_directory[pd_index] & 0xFFFFF000);
    page_table[pt_index] = (phys & 0xFFFFF000) | (flags & 0xFFF) | 0x1;

    // Flush TLB for this page
    asm volatile("invlpg (%0)" ::"r"(virt) : "memory");
}

void unmap_page(uint32_t virt) {
    uint32_t pd_index = virt >> 22; // Top 10 bits
    uint32_t pt_index = (virt >> 12) & 0x3ff; // Next 10 bits

    uint32_t* page_table = first_page_table;
    page_table[pt_index] = 0; // Clears the entry

    // Flush TLB
    asm volatile("invlpg (%0)" ::"r"(virt) : "memory");
}