#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test-model.h"

static void test_check_enomem(void* ptr) {
    if (ptr == NULL) {
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
    return (test_modules_t*) test_alloc(sizeof(test_modules_t));
}

test_module_t* test_new_module(test_modules_t* mods, const char* name, const char* filename, int linenumber) {
    test_module_t* mod = (test_module_t*) test_alloc(sizeof(test_module_t));

    mod->filename = filename;
    mod->linenumber = linenumber;
    mod->name = name;
    mod->parent = mods;

    if (mods->first == NULL) mods->first = mod;
    if (mods->last != NULL) mods->last->next = mod;
    mods->last = mod;

    return mod;
}

test_instance_t* test_new_instance(test_module_t* module, const char* name, const char* filename, const int linenumber,
                                   const test_func func, const void* params) {
    test_instance_t* inst = (test_instance_t*) test_alloc(sizeof(test_instance_t));

    inst->state = TEST_PENDING;
    inst->filename = filename;
    inst->linenumber = linenumber;
    inst->name = name;
    inst->func = func;
    inst->params = params;
    inst->parent = module;

    if (module->first_instance == NULL) module->first_instance = inst;
    if (module->last_instance != NULL) module->last_instance->next = inst;
    module->last_instance = inst;

    return inst;
}

static void aggregate_instance_results(test_results_t* results, test_instance_t* inst) {
    switch (inst->state) {
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
            fprintf(stderr, "WARN: unexpected test-lib instance state.\n");
            break;
    }
}

void aggregate_test_results(test_modules_t* mods, test_results_t* results) {
    memset(results, 0, sizeof(test_results_t));
    enumerate_test_instances(mods, (test_instance_callback) aggregate_instance_results, results);
}

static void enumerate_test_module(test_module_t* mod, test_instance_callback cb, void* context) {
    test_instance_t* inst = mod->first_instance;
    while (inst != NULL) {
        cb(context, inst);
        inst = inst->next;
    }
}

void enumerate_test_instances(test_modules_t* mods, test_instance_callback cb, void* context) {
    test_module_t* mod = mods->first;
    while (mod != NULL) {
        enumerate_test_module(mod, cb, context);
        mod = mod->next;
    }
}

