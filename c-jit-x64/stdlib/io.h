#ifndef C_JIT_X64_IO_H
#define C_JIT_X64_IO_H

#include "syscall.h"

void put_string(const char* s);

void put_long(long v);

#endif //C_JIT_X64_IO_H