#include "kheap.h"
#include "heap.h"
#include "tty.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init() {

  kernel_heap_table.entries =
      (HEAP_BLOCK_TABLE_ENTRY *)(KERNEL_HEAP_TABLE_ADDRESS);
  kernel_heap_table.total_entries = KERNEL_HEAP_TOTAL_ENTRIES;

  void *end = (void *)(KERNEL_HEAP_ADDRESS + KERNEL_HEAP_SIZE);

  int res = heap_create(&kernel_heap, (void *)KERNEL_HEAP_ADDRESS, end,
                        &kernel_heap_table);

  if (res < 0) {
    tty_print_default("Failed to init heap!"); // todo: make kernel panic
  } else {
    tty_print_default("Heap is initialized!\n");
  }
}

void *kmalloc(size_t size) { return heap_malloc(&kernel_heap, size); }

void *kfree(void *ptr) { return heap_free(&kernel_heap, ptr); }