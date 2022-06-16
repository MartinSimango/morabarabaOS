#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

void *memset(void *ptr, int c, size_t size);

void *memcpy(void *dst, const void *src, size_t n);

#endif