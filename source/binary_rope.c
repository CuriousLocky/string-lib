#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"
#include "binary_rope.h"


static uint32_t get_child_length(uint32_t info) {
    return info & 0x7FFFFFFF;
}

static bool child_is_leaf(uint32_t info) {
    return info >= 0x80000000;
}

static uint32_t make_child_info(uint32_t length, bool is_leaf) {
    return length | (is_leaf ? 0x80000000 : 0);
}

uint32_t get_binary_rope_length(BinaryRopeHeader *header) {
    uint32_t left_len = get_child_length(header->left_info);
    uint32_t right_len = get_child_length(header->right_info);
    return left_len + right_len;
}

uint64_t *initialize_binary_rope(uint64_t *left, uint32_t left_len, bool is_leaf_left, uint64_t *right, uint32_t right_len, bool is_leaf_right) {
    BinaryRopeHeader *header = (BinaryRopeHeader *)allocate(sizeof(BinaryRopeHeader));
    header->left_info = make_child_info(left_len, is_leaf_left);
    header->right_info = make_child_info(right_len, is_leaf_right);
    return (uint64_t *)header;
}

static char get_child_charat(uint32_t info, uint32_t index, uint64_t *data) {
    if (child_is_leaf(info)) {
        return ((BinaryRopeLeaf *)data)->bytes[index];
    }
    return get_binary_rope_charat(index, data);
}

char get_binary_rope_charat(uint32_t index, uint64_t *data) {
    BinaryRopeHeader *header = (BinaryRopeHeader *)data;
    uint32_t left_len = get_child_length(header->left_info);
    if (index < left_len) {
        return get_child_charat(header->left_info, index, header->left);
    } else {
        return get_child_charat(header->right_info, index - left_len, header->right);
    }
}

void materialize_binary_rope(uint64_t *data, void *buffer) {
    BinaryRopeHeader *header = (BinaryRopeHeader *)data;
    uint32_t left_len = get_child_length(header->left_info);
    uint8_t *buffer_ptr = (uint8_t *)buffer;
    if (child_is_leaf(header->left_info)) {
        BinaryRopeLeaf *left = (BinaryRopeLeaf *)header->left;
        memcpy(buffer_ptr, left->bytes, left->length);
        buffer_ptr += left->length;
    } else {
        materialize_binary_rope(header->left, buffer_ptr);
        buffer_ptr += left_len;
    }
    if (child_is_leaf(header->right_info)) {
        BinaryRopeLeaf *right = (BinaryRopeLeaf *)header->right;
        memcpy(buffer_ptr, right->bytes, right->length);
    } else {
        materialize_binary_rope(header->right, buffer_ptr);
    }
    deallocate(data);
}