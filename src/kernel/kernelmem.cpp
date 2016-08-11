#include "kernelmem.hh"

KernelMem::KernelMem(uint8_t* start, uint8_t length) {
	this->head = (struct KMallocChunk*) start;
	this->head->state = CHUNK_FREE;
	this->head->length = length;
	this->head->prev = 0;
	this->head->next = 0;
}

void* KernelMem::alloc(uint8_t length) {
	// Round up the allocable length to avoid fragmentation.
	uint8_t extra = length % KUNIT;
	if (extra) {
		length+= (KUNIT - extra);
	}

	length += KUNIT;

	struct KMallocChunk *c = this->head;

	// Iterate over chunks to try and find a usable one.
	while(1) {
		if (!c) {
			// Error! out of memory.
			return 0;
		}
		if (c->state == CHUNK_FREE && c->length >= length) break;
		c = c->next;
	}

	// If the chunk is really large, split it to fit the demands.
	if (length - c->length > 2 * KUNIT) {
		this->split(c, length);
	}

	c->state = CHUNK_USED;

	// Return a pointer to the memory area just after the chunk header.
	return (void*) (c + 1);
}

void KernelMem::free(void* ptr) {
	struct KMallocChunk* c = (struct KMallocChunk*) ptr;
	c--;

	if (c->state != CHUNK_USED) {
		return;
	}

	c->state = CHUNK_FREE;
	this->merge(c);
	this->merge(c->prev);
}

void KernelMem::split(struct KMallocChunk* chunk, uint8_t length) {
	struct KMallocChunk* next = (struct KMallocChunk*)((char*)chunk + length);

	next->state = CHUNK_FREE;
	next->length = chunk->length - length;
	next->prev = chunk;
	next->next = chunk->next;

	if (chunk->next) chunk->next->prev = next;

	chunk->next = next;
	chunk->length = length;
}

void KernelMem::merge(struct KMallocChunk* chunk) {
	if (!chunk) return;

	if (chunk->state != CHUNK_FREE) return;

	if (chunk->next && chunk->next->state == CHUNK_FREE) {
		chunk->length += chunk->next->length;
		if (chunk->next->next) {
			chunk->next->prev = chunk;
		}
		chunk->next = chunk->next->next;
	}
}

