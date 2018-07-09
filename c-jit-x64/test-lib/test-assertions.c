#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include "test-assertions.h"
#include "test-utils.h"

void assert_fail(char* msg, ...) {
    if(msg == NULL) {
        print_failure("Assertion failed.");
    } else {
        va_list arglist;
        va_start(arglist, msg);
        vprint_failure(msg, arglist);
        va_end(arglist);
    }

    exit(TEST_FAILED);
}

void assert_bool_msg(bool actual, bool expected, char* msg, ...) {
    bool success = (!actual && expected) || (actual && !expected);

    if(!success) {
        print_failure("Assertion failed: Expected %s but was %s.  ",
                      expected ? "true" : "false",
                      actual ? "true" : "false");

        if(msg != NULL) {
            va_list arglist;
            va_start(arglist, msg);
            vprint_failure(msg, arglist);
            va_end(arglist);
            print_failure(" ");
        }

        exit(TEST_FAILED);
    }
}

void assert_signed_msg(long actual, op_t op, long expected, char* msg, ...) {
    bool success;
    char* op_string;
    switch(op) {
        case LT:
            success = actual < expected;
            op_string = "less than";
            break;
        case LE:
            success = actual <= expected;
            op_string = "less than or equal to";
            break;
        case EQ:
            success = actual == expected;
            op_string = "equal to";
            break;
        case GE:
            success = actual >= expected;
            op_string = "greater than or equal to";
            break;
        case GT:
            success = actual > expected;
            op_string = "greater than";
            break;
        default:
            assert_fail("Unexpected op: %d", op);
            success = false;
            op_string = NULL;
            break;
    }

    if(!success) {
        print_failure("Assertion failed: %ld was not %s %ld. ", actual, op_string, expected);

        if(msg != NULL) {
            va_list arglist;
            va_start(arglist, msg);
            vprint_failure(msg, arglist);
            va_end(arglist);
            print_failure(" ");
        }

        exit(TEST_FAILED);
    }
}
