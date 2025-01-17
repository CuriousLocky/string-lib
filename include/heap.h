#include <stdint.h>

// Allocate memory on the heap
uint64_t *allocate(uint64_t size);

// Free memory on the heap
void deallocate(uint64_t *ptr);
