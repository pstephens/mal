#include <stdbool.h>
#include <stddef.h>
#include "test-module-self.h"
#include "test-runner.h"
#include "test-utils.h"
#include "test-assertions.h"

static void match_test_case(const char* pattern, const char* str, bool expected) {
    assert_bool(wildcard_match(str, pattern), expected,
                "Assertion Failed: wildcard_match(%s, %s) was not %s.", str, pattern, expected ? "true" : "false");
}

DEFINE_TEST_INSTANCE(match_should_handle_wildcards_properly) {
        match_test_case("g*ks", "geeks", true);
        match_test_case("ge?ks*", "geeksforgeeks", true);
        match_test_case("g*k", "gee", false);
        match_test_case("geek", "geek", true);
        match_test_case("geek", "gee", false);
        match_test_case("gee", "geek", false);
        match_test_case("*pqrs", "pqrst", false);
        match_test_case("abc*bcd", "abcdhghgbcd", true);
        match_test_case("abc*c?d", "abcd", false);
        match_test_case("*c*d", "abcd", true);
        match_test_case("*?c*d", "abcd", true);
        match_test_case("f**l", "football", true);
}

void add_test_runner_tests_module(test_modules_t* mods) {
    test_module_t* mod = ADD_TEST_MODULE(mods, test-module-self);

    ADD_TEST_INSTANCE(mod, match_should_handle_wildcards_properly, NULL);
}