#ifndef C_JIT_X64_IO_H
#define C_JIT_X64_IO_H

#include "syscall.h"

size_t strlen(const char* s);

void puts(const char* s);

void put_long(long v);

#endif //C_JIT_X64_IO_H
