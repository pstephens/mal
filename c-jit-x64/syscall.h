#ifndef C_JIT_X64_SYSCALL_H
#define C_JIT_X64_SYSCALL_H

#include "stdlib.h"

long syscall_write(unsigned int fd, const char* buff, size_t count);

void syscall_exit(int exit_code);

#endif // C_JIT_X64_SYSCALL_H
