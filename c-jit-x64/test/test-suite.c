#include <stdio.h>

#include "heap-tests.h"

int main(int argc, char** argv) {

    add_heap_tests_module();
    add_test_runner_tests_module();

    print_test_modules();

    return test_runner("*", "*");
}