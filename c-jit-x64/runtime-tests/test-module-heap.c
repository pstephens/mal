#include <stddef.h>
#include "test-model.h"

DEFINE_TEST_INSTANCE(foo) {
}

DEFINE_TEST_MODULE(stdlib_heap) {
    ADD_TEST_INSTANCE(foo, NULL);
}
