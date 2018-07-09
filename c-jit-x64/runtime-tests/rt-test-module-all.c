#include "test-model.h"

void rt_register_test_modules(test_modules_t* mods) {
    ADD_TEST_MODULE(mods, runtime_funcs);
    ADD_TEST_MODULE(mods, runtime_heap);
    ADD_TEST_MODULE(mods, runtime_mem_ops);
}
