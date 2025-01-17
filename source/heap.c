#include <stdlib.h>
#include <stdint.h>

uint64_t *allocate(uint64_t size) {
    return (uint64_t *)malloc(size);
}

void deallocate(uint64_t *ptr) {
    free((void *)ptr);
}