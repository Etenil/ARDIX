#ifndef KERNELMEM_HH
#define KERNELMEM_HH

#include <inttypes.h>

/* The first byte of a page is used to determine its state. The following
 * magic numbers are used for that. */
#define CHUNK_FREE 0xFF
#define CHUNK_USED 0xFE

struct KMallocChunk {
	uint8_t state;
	uint8_t length;
	struct KMallocChunk* prev;
	struct KMallocChunk* next;
};

#define KUNIT sizeof(struct KMallocChunk)

class KernelMem
{
private:
	void split(struct KMallocChunk* chunk, uint8_t length);
	void merge(struct KMallocChunk* chunk);

	struct KMallocChunk* head = 0;

public:
	KernelMem(uint8_t* start, uint8_t length);
	void* alloc(uint8_t length);
	void free(void* ptr);
};

#endif

