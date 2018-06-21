#ifndef C_JIT_X64_TEST_RUNNER_H
#define C_JIT_X64_TEST_RUNNER_H

#include <stdbool.h>

typedef enum {
    TEST_PENDING = 0,
    TEST_PASSED = 1,
    TEST_FAILED = 2
} test_state;

struct test_instance;
struct test_module;
typedef struct test_instance test_instance_t;
typedef struct test_module test_module_t;
typedef void (*test_func)(const test_instance_t* instance);

typedef struct test_info {
    const char* name;
    const char* filename;
    const int linenumber;
} test_info_t;

struct test_instance {
    test_state state;
    const char* filename;
    int linenumber;
    const char* name;
    const void* params;
    test_func func;
    test_instance_t* next;
};

struct test_module {
    test_state state;
    const char* filename;
    int linenumber;
    const char* name;
    test_instance_t* first_instance;
    test_instance_t* last_instance;
    test_module_t* next;
};

test_module_t* test_new_module(char* name, char* filename, int linenumber);

test_instance_t* test_new_instance(test_module_t* module, const char* name, const char* filename,
                                   int linenumber, test_func func, const void* params);

#define DEFINE_TEST_INSTANCE(NAME) \
static test_info_t NAME ## __info = { #NAME, __FILE__, __LINE__ }; \
static void NAME(const test_instance_t* metadata)

#define ADD_TEST_INSTANCE(MOD, NAME, PARAMS) \
    (test_new_instance(MOD, NAME ## __info.name, NAME ## __info.filename, NAME ## __info.linenumber, NAME, PARAMS))

#define ADD_TEST_MODULE(NAME) test_new_module(#NAME, __FILE__, __LINE__)

void print_test_modules();

void test_runner(const char* module_filter, const char* instance_filter);

typedef struct {
    long count_failed;
    long count_passed;
    long count_pending;
} test_results_t;

void aggregate_test_results(test_results_t* results);

typedef enum assert_ops {
    LT,
    LE,
    EQ,
    GE,
    GT,
} op_t;

void assert_bool(bool actual, bool expected, char* msg, ...);

void assert_signed(long actual, op_t op, long expected, char* msg, ...);

void assert_unsigned(unsigned long actual, op_t op, unsigned long expected, char* msg, ...);

void add_test_runner_tests_module();

#endif //C_JIT_X64_TEST_RUNNER_H
