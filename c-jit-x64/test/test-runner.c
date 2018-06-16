#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

test_instance_t* test_new_instance(test_module_t* module, char* name, char* filename, int linenumber, test_func func, void* params) {
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