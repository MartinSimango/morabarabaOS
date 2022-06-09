#pragma once
#include <types.h>

void kheap_init();

void *kmalloc(size_t size);

void *kfree(void *ptr);