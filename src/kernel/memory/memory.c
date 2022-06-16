

#include "memory.h"
#include "tty.h"

void *memset(void *ptr, int c, size_t size) {

  char *c_ptr = (char *)ptr;
  for (size_t i = 0; i < size; i++) {
    c_ptr[i] = c;
  }
  return ptr;
}

void *memcpy(void *dst, const void *src, size_t n) {
  uint8 *d = dst;
  const uint8 *s = src;
  
  while (n-- > 0) {
    *d++ = *s++;
  }

  return d;
}