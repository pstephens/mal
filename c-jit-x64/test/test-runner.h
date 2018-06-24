#ifndef C_JIT_X64_TEST_RUNNER_H
#define C_JIT_X64_TEST_RUNNER_H

#include <stdbool.h>
#include "test-model.h"

void test_runner(test_modules_t* mods, const char* module_filter, const char* instance_filter);

#endif //C_JIT_X64_TEST_RUNNER_H
