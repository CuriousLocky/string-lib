#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "linear_string.h"

uint64_t *initialize_linear_string(uint64_t *bytes, uint32_t length) {
    // Allocate memory on the heap
    uint64_t *linear_string = allocate(length);
    LinearStringHeader *header = (LinearStringHeader *)linear_string;
    header->length = length;

    // Copy bytes into linear string
    memcpy(header->bytes, bytes, length);
    return linear_string;
}

void materialize_linear_string(uint64_t *linear_string, void *buffer) {
    LinearStringHeader *header = (LinearStringHeader *)linear_string;
    memcpy(buffer, header->bytes, header->length);
    deallocate(linear_string);
}

char get_linear_string_charat(uint32_t index, uint64_t *linear_string) {
    LinearStringHeader *header = (LinearStringHeader *)linear_string;
    return header->bytes[index];
}