#ifndef TEST_ASSERTIONS_H
#define TEST_ASSERTIONS_H

#include <stdbool.h>

typedef enum assert_ops {
    LT,
    LE,
    EQ,
    GE,
    GT,
} op_t;

void assert_fail(char* msg, ...);

void assert_bool_msg(bool actual, bool expected, char* msg, ...);

inline void assert_bool(bool actual, bool expected) {
    assert_bool_msg(actual, expected, NULL);
}

void assert_signed_msg(long actual, op_t op, long expected, char* msg, ...);

inline void assert_signed(long actual, op_t op, long expected) {
    assert_signed_msg(actual, op, expected, NULL);
}

void assert_unsigned(unsigned long actual, op_t op, unsigned long expected, char* msg, ...);

#endif //TEST_ASSERTIONS_H
