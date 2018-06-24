#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test-model.h"

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

test_modules_t* test_new_modules() {
    return (test_modules_t*)test_alloc(sizeof(test_modules_t));
}

test_module_t* test_new_module(test_modules_t* mods, char* name, char* filename, int linenumber) {
    test_module_t* mod = (test_module_t*)test_alloc(sizeof(test_module_t));

    mod->filename = filename;
    mod->linenumber = linenumber;
    mod->name = name;

    if(mods->first == NULL) mods->first = mod;
    if(mods->last != NULL) mods->last->next = mod;
    mods->last = mod;

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

static void aggregate_module_results(test_module_t* mod, test_results_t* results) {
    test_instance_t* instance = mod->first_instance;
    while(instance != NULL) {
        switch(instance->state) {
            case TEST_PASSED:
                results->count_passed++;
                break;
            case TEST_FAILED:
                results->count_failed++;
                break;
            case TEST_PENDING:
                results->count_pending++;
                break;
            default:
                fprintf(stderr, "WARN: unexpected test instance state.\n");
                break;
        }

        instance = instance->next;
    }
}

void aggregate_test_results(test_modules_t* mods, test_results_t* results) {
    memset(results, 0, sizeof(test_results_t));
    test_module_t* pos = mods->first;
    while(pos != NULL) {
        aggregate_module_results(pos, results);
        pos = pos->next;
    }
}