#pragma once

#include "types.h"
#include "vbe.h"
#define KERNEL_HEAP_SIZE 100 * MEGABYTE
#define KERNEL_HEAP_BLOCK_SIZE 4096
#define KERNEL_HEAP_TOTAL_ENTRIES                                              \
  KERNEL_HEAP_SIZE / KERNEL_HEAP_BLOCK_SIZE // 25600 entries for 4096 block size
#define KERNEL_HEAP_ADDRESS 0x01000000
#define KERNEL_HEAP_TABLE_ADDRESS                                              \
  (VBE_MODE_INFO_ADDRESS + VBE_BLOCK_SIZE) // start after the VBE section

// ****************HEAP ENTRY STRUCTURE**********************
// (UPPER 4 BITS ARE FLAGS)
// (LOWER 4 BITS ARE ENTRY TYPE)
// HAS_NEXT, IS_FIRST, 0, 0, ET3, ET2, ET1, ET0
// ****************HEAP ENTRY STRUCTURE**********************
// HAS_NEXT - is the next block part of same allocation
// IS_FIRST - is this the first block in the allocation
// 0 - not used 
// ET3 - not used
// ET2 - not used
// ET1 - Block is taken
// ET0 - Block is free

// first 4 bits (lower 4 bits)
// ENTRY_TYPE

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0X01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0X00

// two top bits
#define HEAP_BLOCK_TABLE_ENTRY_HAS_NEXT 0b10000000 // 0x80
#define HEAP_BLOCK_TABLE_ENTRY_IS_FIRST 0b01000000 // 0x40 0xc1 0b11000001

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

struct heap_table {
  // an array of all entries each entry will represent 4096 bytes of memory
  // have a pointer pointing to somewhere in RAM. entries will take up
  // 1*total_entries bytes
  HEAP_BLOCK_TABLE_ENTRY *entries;
  size_t total_entries;
};

struct heap {
  struct heap_table *table;
  void *start_address;
};

int heap_create(struct heap *heap, void *start, void *end,
                struct heap_table *table);

void *heap_malloc(struct heap *heap, size_t size);

void *heap_free(struct heap *heap, void *ptr);
