#ifndef _STRING_
#define _STRING_


#include "util.h"

size_t strlen(const char * string) {

    size_t len = 0;
    while(string[len]) {
        len++;
    }
    return len;

}

#endif






