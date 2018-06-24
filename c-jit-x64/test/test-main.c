#include <stdio.h>

#include "test-module-heap.h"
#include "test-runner.h"

extern void add_test_runner_tests_module(test_modules_t* mods);

int main(int argc, char** argv) {

    test_modules_t* mods = test_new_modules();

    add_heap_tests_module(mods);
    add_test_runner_tests_module(mods);

    test_runner(mods, "*", "*");

    test_results_t results;
    aggregate_test_results(mods, &results);

    fprintf(stderr, "\nTEST RESULTS: %ld PASSED, %ld FAILED, %ld SKIPPED",
            results.count_passed, results.count_failed, results.count_pending);

    return results.count_failed > 0 ? 1 : 0;
}