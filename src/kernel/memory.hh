#ifndef MEMORY_HH
#define MEMORY_HH

#include <inttypes.h>

#include "console.hh"

#include "platform/arduino_nano.h"

#define KILO 1024
#define MEGA (KILO*KILO)
#define GIGA (KILO*KILO*KILO)

class Memory {
private:
	uint8_t pages_free = 0;
	uint8_t pages_total = 0;

	uint8_t* pagemap = 0;
	uint8_t pagemap_bits = 0;
	uint8_t pagemap_bytes = 0;
	uint8_t pagemap_pages = 0;
	uint8_t pagemap_cells = 0;

	void* main_memory_start = (void*)MAIN_MEMORY_START;

	Console* console;

public:
	Memory(Console* console);
	void* allocPage(bool write_zero);
	void freePage(void *addr);
};

#endif

