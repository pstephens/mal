#include <stddef.h>
#include "test-model.h"

DEFINE_TEST_INSTANCE(foo) {
}

DEFINE_TEST_MODULE(runtime_heap) {
    ADD_TEST_INSTANCE(foo, NULL);
}
