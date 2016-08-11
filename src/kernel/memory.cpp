#include <string.h>

#include "memory.hh"

Memory::Memory() {
	pages_total = (uint8_t)(TOTAL_MEMORY / PAGE_SIZE);
	pages_free = pages_total;

	pagemap = (uint8_t*)main_memory_start;
	pagemap_bits = (TOTAL_MEMORY - MAIN_MEMORY_START) / PAGE_SIZE;
	pagemap_bytes = 1 + pagemap_bits / 8;
	pagemap_pages = 1 + pagemap_bytes / PAGE_SIZE;

	// Fill memory with FF to keep it clean.
	memset(pagemap, PAGE_FREE, pagemap_bytes);

	// Initialise all memory pages.
	uint8_t i;
	for(i = 0; i < pagemap_pages; i++) {
		this->allocPage(true);
	}
}

void* Memory::allocPage(bool write_zero) {
	uint8_t page_byte_num;
	uint8_t bit_num;
	uint8_t mask;
	uint8_t page_number;
	void* page_addr;

	if (!pagemap) { // Memory not initialised!
		return 0;
	}

	// Iterate on each bit of the pagemap until finding a free page.
	for (page_byte_num = 0; page_byte_num < pagemap_bytes; page_byte_num++) {
		for (bit_num = 0; bit_num < 8; bit_num++) {
			mask = 1 << bit_num;
			if (pagemap[page_byte_num] & mask) {
				// Mark the page as allocated.
				pagemap[page_byte_num] &= ~mask;

				page_number = page_byte_num * 8 + bit_num;
				page_addr = (page_number * PAGE_SIZE + MAIN_MEMORY_START);

				if (write_zero) {
					memset(page_addr, 0, PAGE_SIZE);
				}

				pages_free--;
				return page_addr;
			}
		}
	}

	// This fails and should show some kind of error.
	return 0;
}

