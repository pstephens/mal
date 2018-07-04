#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include "test-assertions.h"
#include "test-utils.h"

void assert_bool(bool actual, bool expected, char* msg, ...) {
    if((!actual && expected) || (actual && !expected)) {
        if(msg == NULL) {
            print_failure("Expected %s but was %s.", expected ? "true" : "false", actual ? "true" : "false");
        } else {
            va_list arglist;
            va_start(arglist, msg);
            vprint_failure(msg, arglist);
            va_end(arglist);
        }

        exit(TEST_FAILED);
    }
}

/*void assert_signed(long actual, op_t op, long expected, char* msg, ...);

void assert_unsigned(unsigned long actual, op_t op, unsigned long expected, char* msg, ...);*/
