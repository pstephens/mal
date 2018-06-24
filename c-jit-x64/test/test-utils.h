#ifndef C_JIT_X64_TEST_UTILS_H
#define C_JIT_X64_TEST_UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include "test-model.h"

bool wildcard_match(const char *str, const char *pattern);

void print_instance_name(test_module_t* mod, test_instance_t* instance, char* prefix, char* suffix);

void vprint_failure(char* msg, va_list args);

void print_failure(char* msg, ...);

void print_success(char* msg, ...);

void print_test_modules(test_modules_t* mods);

#endif //C_JIT_X64_TEST_UTILS_H
