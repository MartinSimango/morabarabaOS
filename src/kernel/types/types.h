#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef unsigned int size_t;

#define NULL ((void *)0)

#define KILOBYTE 1024
#define MEGABYTE (1024 * 1024)

static inline char *itoa(uint32 x, char *s, size_t sz) {

  uint32 tmp;
  int i, j;

  tmp = x;
  i = 0;

  do {
    tmp = x % 10;
    s[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
  } while (x /= 10);
  s[i--] = 0;

  for (j = 0; j < i; j++, i--) {
    tmp = s[j];
    s[j] = s[i];
    s[i] = tmp;
  }

  return s;
}

#endif