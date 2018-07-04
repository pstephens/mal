#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include "test-utils.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

// adapted from https://www.geeksforgeeks.org/wildcard-character-matching/
// pattern allows ? or * wildcard characters.
// ? substitutes exactly one character
// * substitutes zero or more characters
bool wildcard_match(const char *str, const char *pattern) {
    while(true) {
        if(*str == 0) {
            if(*pattern == 0) {
                return true;
            }
            else if(*pattern == '*') {
                pattern++;
                continue;
            }
            else {
                return false;
            }
        } else if(*pattern == 0) {
            return false;
        } else if(*pattern == '*') {
            if(wildcard_match(str + 1, pattern)) {
                return true;
            } else {
                pattern++;
                continue;
            }
        } else if(*pattern == '?' || toupper(*str) == toupper(*pattern)) {
            str++;
            pattern++;
            continue;
        } else {
            return false;
        }
    }
}

void print_instance_name(test_module_t* mod, test_instance_t* instance, char* prefix, char* suffix) {
    fprintf(stderr, "%s%s/%s%s", prefix, mod->name, instance->name, suffix);
}

void vprint_failure(char* msg, va_list args) {
    vfprintf(stderr, msg, args);
}

void print_failure(char* msg, ...) {
    va_list arglist;
    va_start(arglist, msg);
    vprint_failure(msg, arglist);
    va_end(arglist);
}

void print_success(char* msg, ...) {
    va_list arglist;
    va_start(arglist, msg);
    vfprintf(stderr, msg, arglist);
    va_end(arglist);
}

static void print_test_instance(void* context,  const test_instance_t* inst) {
    fprintf(stdout, "%s|%s|%s:%d\n", inst->parent->name, inst->name, inst->filename, inst->linenumber);
}

void print_test_modules(test_modules_t* mods) {
    enumerate_test_instances(mods, print_test_instance, NULL);
}

#pragma clang diagnostic pop