#include "heap.h"
#include "memory.h"
#include "status.h"
// #include "terminal.h"

static int heap_validate_heap_table(void *start, void *end,
                                    struct heap_table *table) {
  int res = 0;

  size_t table_size = (size_t)(end - start);
  size_t total_blocks = table_size / KERNEL_HEAP_BLOCK_SIZE;
  if (total_blocks != table->total_entries) {
    return -EINVARG;
  }
  return res;
}

static int heap_validate_alignment(void *ptr) {
  return ((unsigned int)ptr % KERNEL_HEAP_BLOCK_SIZE) == 0;
}

int heap_create(struct heap *heap, void *start, void *end,
                struct heap_table *table) {

  int res = 0;
  if (!heap_validate_alignment(start) || !heap_validate_alignment(end)) {
    return -EINVARG;
  }

  memset(heap, 0, sizeof(struct heap)); // initliaze heap struct to 0
  heap->start_address = start;
  heap->table = table;

  res = heap_validate_heap_table(start, end, table);

  if (res < 0) {
    return res;
  }

  size_t table_size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total_entries;
  // initialize all heap table entries to be FREE (0x00)
  memset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);
  return 0;
}

static uint32 heap_align_value_to_upper(uint32 block_size) {
  if ((block_size % KERNEL_HEAP_BLOCK_SIZE) == 0) {
    return block_size;
  }
  return block_size + KERNEL_HEAP_BLOCK_SIZE - (block_size % KERNEL_HEAP_BLOCK_SIZE);
}

static uint8 heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry) {
  return entry & 0x0f; // get the lower 4 bits of the heap entry which is the entry type
}

static uint32 heap_get_start_block(struct heap *heap, uint32 total_blocks) {
  uint32 start_block = 0;
  uint32 continuous_blocks = 0;

  struct heap_table *table = heap->table;
  for (uint32 i = 0; i < table->total_entries; i++) {
    if (heap_get_entry_type(table->entries[i]) != HEAP_BLOCK_TABLE_ENTRY_FREE) {
      continuous_blocks = 0;
      continue;
    }

    continuous_blocks++;
    if (continuous_blocks == 1) {
      start_block = i;
    }
    if (continuous_blocks == total_blocks) {
      break;
    }
  }

  if (continuous_blocks == 0) {
    return -ENOMEM; // out of memory
  }
  return start_block;
}

void *heap_block_to_address(struct heap *heap, uint32 start_block) {
  return (void *)(heap->start_address + (KERNEL_HEAP_BLOCK_SIZE * start_block));
}

void heap_mark_blocks_taken(struct heap_table *table, uint32 start_block,
                            uint32 blocks) {

  uint32 end_block = start_block + blocks - 1;
  table->entries[start_block] =
      HEAP_BLOCK_TABLE_ENTRY_IS_FIRST | HEAP_BLOCK_TABLE_ENTRY_TAKEN;
  if (blocks > 1) {
    table->entries[start_block] |= HEAP_BLOCK_TABLE_ENTRY_HAS_NEXT;
  }

  for (uint32 i = start_block + 1; i < end_block; i++) {
    table->entries[i] =
        HEAP_BLOCK_TABLE_ENTRY_TAKEN | HEAP_BLOCK_TABLE_ENTRY_HAS_NEXT;
  }
  table->entries[end_block] = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
}

void *heap_malloc_block(struct heap *heap, uint32 blocks) {
  uint32 start_block = heap_get_start_block(heap, blocks);
  if (start_block < 0) {
    // terminal_kernel_panic(start_block);
  }

  heap_mark_blocks_taken(heap->table, start_block, blocks);

  return heap_block_to_address(heap, start_block);
}

void *heap_malloc(struct heap *heap, size_t size) {

  size_t aligned_size = heap_align_value_to_upper(size);
  uint32 total_blocks = aligned_size / KERNEL_HEAP_BLOCK_SIZE;

  return heap_malloc_block(heap, total_blocks);
}

static uint32 heap_address_to_block(struct heap *heap, void *address) {
  uint32 offset_addr = (uint32)(address - heap->start_address);

  if (!heap_validate_alignment(address) ||
      !heap_validate_alignment((void *)offset_addr) || address == NULL ||
      offset_addr < 0) {
    return -EINVARG;
  }

  return offset_addr / KERNEL_HEAP_BLOCK_SIZE;
}

static void heap_mark_blocks_free(struct heap *heap, uint32 start_block) {

  uint32 current_block = start_block;
  struct heap_table *table = heap->table;
  while (current_block < heap->table->total_entries) {

    table->entries[current_block] = HEAP_BLOCK_TABLE_ENTRY_FREE;
    if (!(heap->table->entries[current_block] &
          HEAP_BLOCK_TABLE_ENTRY_HAS_NEXT)) {
      break;
    }
    current_block++;
  }

  // Below will zero out memory that was freed (not that necessary)
  uint32 number_of_blocks = current_block - start_block + 1;
  memset(heap->start_address + (start_block * KERNEL_HEAP_BLOCK_SIZE), 0,
         (number_of_blocks * KERNEL_HEAP_BLOCK_SIZE));
}

void *heap_free(struct heap *heap, void *ptr) {

  int start_block = heap_address_to_block(heap, ptr);
  if (start_block < 0) {
    // terminal_kernel_panic(start_block);
  }

  heap_mark_blocks_free(heap, start_block);

  return ptr;
}