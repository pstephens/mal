#ifndef RUNTIME_SYSCALL_H
#define RUNTIME_SYSCALL_H

#include "rt-stdlib.h"

long rt_syscall_write(unsigned int fd, const char* buff, size_t count);

void rt_syscall_exit(int exit_code);

#endif // RUNTIME_SYSCALL_H
