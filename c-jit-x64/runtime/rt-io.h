#ifndef RUNTIME_IO_H
#define RUNTIME_IO_H

#include "rt-syscall.h"

void rt_put_string(const char* s);

void rt_put_long(long v);

#endif //RUNTIME_IO_H