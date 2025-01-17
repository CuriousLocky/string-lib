#ifndef BINARY_ROPE_H
#define BINARY_ROPE_H

#include <stdint.h>

// Binary rope leaf node
typedef struct {
    uint16_t length;
    uint8_t bytes[];
} BinaryRopeLeaf;

// Binary rope header structure
typedef struct {
    uint32_t left_info;
    uint32_t right_info;
    void *left;
    void *right;
} BinaryRopeHeader;

// Get the length of the binary rope
uint32_t get_binary_rope_length(BinaryRopeHeader *header);

// Initialize a binary rope with the given left and right children
uint64_t *initialize_binary_rope(uint64_t *left, uint32_t left_len, bool is_leaf_left, uint64_t *right, uint32_t right_len, bool is_leaf_right);

// Get the character at the given index in the binary rope
char get_binary_rope_charat(uint32_t index, uint64_t *data);

// Materialize the binary rope into a buffer
void materialize_binary_rope(uint64_t *data, void *buffer);

#endif