#include "syscall.h"

void _start() {
    char x[] = "Hello, World\n";
    syscall_write(0, x, sizeof(x) - 1);
    syscall_exit(42);
}