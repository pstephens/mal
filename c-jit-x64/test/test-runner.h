#ifndef C_JIT_X64_TEST_RUNNER_H
#define C_JIT_X64_TEST_RUNNER_H

typedef enum {
    TEST_PENDING = 0,
    TEST_PASSED = 1,
    TEST_FAILED = 2
} test_state;

struct test_instance;
struct test_module;
typedef struct test_instance test_instance_t;
typedef struct test_module test_module_t;
typedef test_state (*test_func)(test_instance_t* metadata);

typedef struct test_info {
    char* name;
    char* filename;
    int linenumber;
} test_info_t;

struct test_instance {
    test_state state;
    char* filename;
    int linenumber;
    char* name;
    void* params;
    test_func func;
    test_instance_t* next;
};

struct test_module {
    test_state state;
    char* filename;
    int linenumber;
    char* name;
    test_instance_t* first_instance;
    test_instance_t* last_instance;
    test_module_t* next;
};

test_module_t* test_new_module(char* name, char* filename, int linenumber);

test_instance_t* test_new_instance(test_module_t* module, char* name, char* filename, int linenumber,
                                   test_func func, void* params);

#define DEFINE_TEST_INSTANCE(NAME) \
static test_info_t NAME ## __info = { #NAME, __FILE__, __LINE__ }; \
static test_state NAME(test_instance_t* metadata)

#define ADD_TEST_INSTANCE(MOD, NAME, PARAMS) \
    (test_new_instance(MOD, NAME ## __info.name, NAME ## __info.filename, NAME ## __info.linenumber, NAME, PARAMS))

#define ADD_TEST_MODULE(NAME) test_new_module(#NAME, __FILE__, __LINE__)

void print_test_modules();

#endif //C_JIT_X64_TEST_RUNNER_H
