#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include "test-runner.h"

static void test_check_enomem(void* ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "Out of memory.");
        exit(12);
    }
}

static void* test_alloc(size_t bytes) {
    void* m = malloc(bytes);
    test_check_enomem(m);
    memset(m, 0, bytes);
    return m;
}

static test_module_t* first = NULL;
static test_module_t* last = NULL;

test_module_t* test_new_module(char* name, char* filename, int linenumber) {
    test_module_t* mod = (test_module_t*)test_alloc(sizeof(test_module_t));

    mod->filename = filename;
    mod->linenumber = linenumber;
    mod->name = name;
    mod->state = TEST_PENDING;

    if(first == NULL) first = mod;
    if(last != NULL) last->next = mod;
    last = mod;

    return mod;
}

test_instance_t* test_new_instance(test_module_t* module, const char* name, const char* filename, const int linenumber,
                                   const test_func func, const void* params) {
    test_instance_t* inst = (test_instance_t*)test_alloc(sizeof(test_instance_t));

    inst->state = TEST_PENDING;
    inst->filename = filename;
    inst->linenumber = linenumber;
    inst->name = name;
    inst->func = func;
    inst->params = params;

    if(module->first_instance == NULL) module->first_instance = inst;
    if(module->last_instance != NULL) module->last_instance->next = inst;
    module->last_instance = inst;

    return inst;
}

static void print_test_module(test_module_t* mod) {
    test_instance_t* pos = mod->first_instance;
    while(pos != NULL) {
        fprintf(stdout, "%s|%s|%s:%d\n", mod->name, pos->name, pos->filename, pos->linenumber);
        pos = pos->next;
    }
}

void print_test_modules() {
    test_module_t* pos = first;
    while(pos != NULL) {
        print_test_module(pos);
        pos = pos->next;
    }
}

// adapted from https://www.geeksforgeeks.org/wildcard-character-matching/
// pattern allows ? or * wildcard characters.
// ? substitutes exactly one character
// * substitutes zero or more characters
static bool match(const char* str, const char* pattern) {
    if(*str == 0) {
        if(*pattern == 0)
            return true;
        else if(*pattern == '*')
            return match(str, pattern + 1);
        else
            return false;
    } else if(*pattern == 0) {
        return false;
    } else if(*pattern == '*') {
        return match(str + 1, pattern) || match(str, pattern + 1);
    } else if(*pattern == '?' || toupper(*str) == toupper(*pattern)) {
        return match(str + 1, pattern + 1);
    } else {
        return false;
    }
}

static void print_instance_name(test_module_t* mod, test_instance_t* instance, char* prefix, char* suffix) {
    fprintf(stderr, "%s%s/%s%s", prefix, mod->name, instance->name, suffix);
}

static void vprint_failure(char* msg, va_list args) {
    vfprintf(stderr, msg, args);
}

static void print_failure(char* msg, ...) {
    va_list arglist;
    va_start(arglist, msg);
    vprint_failure(msg, arglist);
    va_end(arglist);
}

static void print_success(char* msg, ...) {
    va_list arglist;
    va_start(arglist, msg);
    vfprintf(stderr, msg, arglist);
    va_end(arglist);
}

static test_state test_instance(test_module_t* mod, test_instance_t* instance) {
    print_instance_name(mod, instance, "Testing ", ": ");
    test_state result;
    pid_t pid = fork();
    if(pid == -1) {
        // Record an error
        print_failure("FAILED while attempting fork. errno=%d\n", errno);
        result = TEST_FAILED;
    } else if(pid == 0) {
        // This is the child process. Execute the test and then exit the process with 0 (success) or 1 (failure).
        instance->func(instance);
        exit(TEST_PASSED);
    } else {
        siginfo_t info;
        if(0 == waitid(P_PID, (id_t) pid, &info, WEXITED | WSTOPPED)) {
            switch(info.si_code) {
                case CLD_EXITED:
                    switch(info.si_status) {
                        case TEST_PASSED:
                            print_success("PASSED\n");
                            result = TEST_PASSED;
                            break;
                        case TEST_FAILED:
                            print_failure("FAILED\n");
                            result = TEST_FAILED;
                            break;
                        default:
                            print_failure("FAILED. exit_code=%d", info.si_status);
                            result = TEST_FAILED;
                            break;
                    }
                    break;
                default:
                    print_failure("FAILED with signal. si_code=%d, si_status=%d\n", info.si_code, info.si_status);
                    result = TEST_FAILED;
                    break;
            }
        } else {
            print_failure("FAILED to wait(). errno=%d\n", errno);
            result = TEST_FAILED;
        }
    }

    instance->state = result;
    return result;
}

static test_state test_module(test_module_t* mod, char* instance_filter) {
    test_instance_t* pos = mod->first_instance;
    test_state result = TEST_PENDING;
    while(pos != NULL) {
        result |= test_instance(mod, pos);
        pos = pos->next;
    }

    return result;
}

test_state test_runner(char* module_filter, char* instance_filter) {
    test_module_t* pos = first;
    test_state result = TEST_PENDING;
    while(pos != NULL) {
        result |= test_module(pos, instance_filter);
        pos = pos->next;
    }

    return result;
}

void assert_bool(bool actual, bool expected, char* msg, ...) {
    if((!actual && expected) || (actual && !expected)) {
        if(msg == NULL) {
            print_failure("Expected %s but was %s.", expected ? "true" : "false", actual ? "true" : "false");
        } else {
            va_list arglist;
            va_start(arglist, msg);
            vprint_failure(msg, arglist);
            va_end(arglist);
        }

        exit(TEST_FAILED);
    }
}

/*void assert_signed(long actual, op_t op, long expected, char* msg, ...);

void assert_unsigned(unsigned long actual, op_t op, unsigned long expected, char* msg, ...);*/




// =========================================
// Test Cases -- tests for the runner itself

static void match_test_case(const char* pattern, const char* str, bool expected) {
    assert_bool(match(str, pattern), expected,
                "Assertion Failed: match(%s, %s) was not %s.", str, pattern, expected ? "true" : "false");
}

DEFINE_TEST_INSTANCE(match_should_handle_wildcards_properly) {
    match_test_case("g*ks", "geeks", true);
    match_test_case("ge?ks*", "geeksforgeeks", true);
    match_test_case("g*k", "gee", false);
    match_test_case("*pqrs", "pqrst", false);
    match_test_case("abc*bcd", "abcdhghgbcd", true);
    match_test_case("abc*c?d", "abcd", false);
    match_test_case("*c*d", "abcd", true);
    match_test_case("*?c*d", "abcd", true);
}

void add_test_runner_tests_module() {
    test_module_t* mod = ADD_TEST_MODULE(test-runner);

    ADD_TEST_INSTANCE(mod, match_should_handle_wildcards_properly, NULL);
}