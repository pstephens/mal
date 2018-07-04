#ifndef TEST_MODEL_H
#define TEST_MODEL_H

typedef enum {
    TEST_PENDING = 0,
    TEST_PASSED = 1,
    TEST_FAILED = 2
} test_state;

typedef struct test_instance test_instance_t;
typedef struct test_module test_module_t;
typedef struct test_modules test_modules_t;
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
    test_module_t* parent;
};

struct test_module {
    const char* filename;
    int linenumber;
    const char* name;
    test_instance_t* first_instance;
    test_instance_t* last_instance;
    test_module_t* next;
    test_modules_t* parent;
};

struct test_modules {
    test_module_t* first;
    test_module_t* last;
};

typedef struct {
    long count_failed;
    long count_passed;
    long count_pending;
} test_results_t;

test_modules_t* test_new_modules();

void free_test_modules(test_modules_t* mods);

test_module_t* test_new_module(test_modules_t* mods, const char* name, const char* filename, int linenumber);

test_instance_t* test_new_instance(test_module_t* module, const char* name, const char* filename,
                                   int linenumber, test_func func, const void* params);

void aggregate_test_results(test_modules_t* mods, test_results_t* results);

#define DEFINE_TEST_INSTANCE(NAME) \
static test_info_t NAME ## __info = { #NAME, __FILE__, __LINE__ }; \
static void NAME(const test_instance_t* metadata)

#define ADD_TEST_INSTANCE(NAME, PARAMS) \
    (test_new_instance(mod, NAME ## __info.name, NAME ## __info.filename, NAME ## __info.linenumber, NAME, PARAMS))

#define DEFINE_TEST_MODULE(NAME) \
static test_info_t NAME ## __mod_info = { #NAME, __FILE__, __LINE__ }; \
static void NAME ## __mod_def(test_module_t* mod); \
void NAME ## __mod(test_modules_t* mods) { \
    test_module_t* mod = test_new_module(mods, \
                                         NAME ## __mod_info.name, \
                                         NAME ## __mod_info.filename, \
                                         NAME ## __mod_info.linenumber); \
    NAME ## __mod_def(mod); \
} \
static void NAME ## __mod_def(test_module_t* mod)

#define ADD_TEST_MODULE(MODS, NAME) \
    extern void NAME ## __mod(test_modules_t* mods); \
    NAME ## __mod(MODS)

typedef void (*test_instance_callback)(void* context, const test_instance_t* instance);

void enumerate_test_instances(test_modules_t* mods, test_instance_callback cb, void* context);

#endif //TEST_MODEL_H
