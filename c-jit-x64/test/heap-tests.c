#include <stddef.h>
#include "heap-tests.h"

DEFINE_TEST_INSTANCE(foo) {
    return TEST_FAILED;
}

void add_heap_tests_module() {
    test_module_t* mod = ADD_TEST_MODULE(heap);

    ADD_TEST_INSTANCE(mod, foo, NULL);
}