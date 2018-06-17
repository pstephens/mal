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
static int match(const char* str, const char* pattern) {
    if(*str == 0) {
        if(*pattern == 0)
            return 1;
        else if(*pattern == '*')
            return match(str, pattern + 1);
        else
            return 0;
    } else if(*pattern == 0) {
        return 0;
    } else if(*pattern == '*') {
        return match(str + 1, pattern) || match(str, pattern + 1);
    } else if(*pattern == '?' || toupper(*str) == toupper(*pattern)) {
        return match(str + 1, pattern + 1);
    } else {
        return 0;
    }
}

static void print_instance_name(test_module_t* mod, test_instance_t* instance, char* msg) {
    fprintf(stderr, "\n%s%s/%s", msg, mod->name, instance->name);
}

static test_state test_instance(test_module_t* mod, test_instance_t* instance) {
    test_state result;
    pid_t pid = fork();
    if(pid == -1) {
        // Record an error
        print_instance_name(mod, instance, "Failed while attempting to fork ");
        fprintf(stderr, ". errno=%d\n", errno);
        result = TEST_FAILED;
    } else if(pid == 0) {
        // This is the child process. Execute the test and then exit the process with 0 (success) or 1 (failure).
        result = instance->func(instance);
        if(result == TEST_PASSED)
            exit(0);
        else
            exit(1);
    } else {
        siginfo_t info;
        if(0 == waitid(P_PID, (id_t) pid, &info, WEXITED | WSTOPPED)) {
            switch(info.si_code) {
                case CLD_EXITED:
                    switch(info.si_status) {
                        case 0:
                            fprintf(stderr, ".");
                            result = TEST_PASSED;
                            break;
                        case 1:
                            fprintf(stderr, "E");
                            result = TEST_FAILED;
                            break;
                        default:
                            print_instance_name(mod, instance, "Failed ");
                            fprintf(stderr, ". exit_code=%d\n", info.si_status);
                            result = TEST_FAILED;
                            break;
                    }
                    break;
                default:
                    print_instance_name(mod, instance, "Failed with wait code ");
                    switch(info.si_code) {
                        case CLD_KILLED:
                            fprintf(stderr, "CLD_KILLED");
                            break;
                        case CLD_DUMPED:
                            fprintf(stderr, "CLD_DUMPED");
                            break;
                        case CLD_STOPPED:
                            fprintf(stderr, "CLD_STOPPED");
                            break;
                        case CLD_TRAPPED:
                            fprintf(stderr, "CLD_TRAPPED");
                            break;
                        case CLD_CONTINUED:
                            fprintf(stderr, "CLD_CONTINUED");
                            break;
                        default:
                            fprintf(stderr, "%d", info.si_code);
                            break;
                    }
                    fprintf(stderr, ", signal=%d\n", info.si_status);
                    result = TEST_FAILED;
                    break;
            }
        } else {
            print_instance_name(mod, instance, "Failed ");
            fprintf(stderr, " while waiting for child process. errno=%d\n", errno);
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