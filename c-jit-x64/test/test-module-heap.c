#include <stddef.h>
#include "test-module-heap.h"

DEFINE_TEST_INSTANCE(foo) {
}

void add_heap_tests_module(test_modules_t* mods) {
    test_module_t* mod = ADD_TEST_MODULE(mods, heap);

    ADD_TEST_INSTANCE(mod, foo, NULL);
}