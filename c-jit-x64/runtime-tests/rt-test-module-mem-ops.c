#include <stddef.h>
#include <string.h>
#include <rt-string.h>
#include <test-assertions.h>
#include <test-model.h>

static void assert_byte_range(char* buff, char expected, size_t offset, size_t len, char* msg) {
    for(; len > 0; --len, ++offset) {
        if(buff[offset] != expected) {
            assert_fail("%s: At offset %d, expected character %d but found %d.", msg, offset, expected, buff[offset]);
        }
    }
}

DEFINE_TEST_INSTANCE(rt_memset) {
    char buff[64];
    memset(buff, 0, 64);

    rt_memset(buff + 5, 17, 10);

    assert_byte_range(buff, 0, 0, 5, "byte range 0");
    assert_byte_range(buff, 17, 5, 10, "byte range 1");
    assert_byte_range(buff, 0, 15, 64-15, "byte range 2");
}

DEFINE_TEST_INSTANCE(rt_memset_zerolen) {
    char buff[64];
    memset(buff, 0, 64);

    rt_memset(buff + 5, 17, 0);

    assert_byte_range(buff, 0, 0, 64, "byte range 0");
}

DEFINE_TEST_INSTANCE(rt_memset_aligned) {
    char buff[1024];
    memset(buff, 0, 1024);

    rt_memset(buff + 8, 17, 1024 - 16);

    assert_byte_range(buff, 0, 0, 8, "byte range 0");
    assert_byte_range(buff, 17, 8, 1008, "byte range 1");
    assert_byte_range(buff, 0, 1016, 8, "byte range 2");
}

DEFINE_TEST_INSTANCE(rt_memzero) {
    char buff[64];
    memset(buff, 42, 64);

    rt_memzero(buff + 8, 24);

    assert_byte_range(buff, 42, 0, 8, "byte range 0");
    assert_byte_range(buff, 0, 8, 24, "byte range 1");
    assert_byte_range(buff, 42, 32, 32, "byte range 2");
}

DEFINE_TEST_MODULE(runtime_mem_ops) {
    ADD_TEST_INSTANCE(rt_memset, NULL);
    ADD_TEST_INSTANCE(rt_memset_zerolen, NULL);
    ADD_TEST_INSTANCE(rt_memset_aligned, NULL);
    ADD_TEST_INSTANCE(rt_memzero, NULL);
}