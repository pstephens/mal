#ifndef RUNTIME_STRING_H
#define RUNTIME_STRING_H

#include "rt-stdlib.h"

size_t rt_strlen(const char* s);

#define rt_memset(s, v, len) ({\
    asm ( \
        "cld\n" \
        "mov %0, %%rdi\n" \
        "mov %1, %%rax\n" \
        "mov %2, %%rcx\n" \
        "rep stosb" \
        :: "x" (s), "x" (v), "x" (len) \
        : "rdi", "rax", "rcx", "cc", "memory"); \
    })

#define rt_memzero(s, len) (rt_memset(s, 0, len))

#endif //RUNTIME_STRING_H
