#ifndef C_JIT_X64_TEST_ASSERTIONS_H
#define C_JIT_X64_TEST_ASSERTIONS_H

#include <stdbool.h>

typedef enum assert_ops {
    LT,
    LE,
    EQ,
    GE,
    GT,
} op_t;

void assert_bool(bool actual, bool expected, char* msg, ...);

void assert_signed(long actual, op_t op, long expected, char* msg, ...);

void assert_unsigned(unsigned long actual, op_t op, unsigned long expected, char* msg, ...);

#endif //C_JIT_X64_TEST_ASSERTIONS_H
