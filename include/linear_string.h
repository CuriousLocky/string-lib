#ifndef LINEAR_STRING_H
#define LINEAR_STRING_H

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "binary_rope.h"

// Linear string header structure
typedef struct {
    uint16_t length;
    uint8_t bytes[];
} LinearStringHeader;

// Linear string is used as a leaf node in the binary rope
static_assert(offsetof(LinearStringHeader, length) == offsetof(BinaryRopeLeaf, length), "LinearStringHeader and BinaryRopeLeaf must have the same layout");
static_assert(offsetof(LinearStringHeader, bytes) == offsetof(BinaryRopeLeaf, bytes), "LinearStringHeader and BinaryRopeLeaf must have the same layout");

// Initialize a linear string with the given bytes and length
uint64_t *initialize_linear_string(uint64_t *bytes, uint32_t length);

// Materialize a linear string into a buffer
void materialize_linear_string(uint64_t *linear_string, void *buffer);

#endif