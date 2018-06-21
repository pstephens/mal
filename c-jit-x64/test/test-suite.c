#include <stdio.h>

#include "heap-tests.h"
#include "test-runner.h"

int main(int argc, char** argv) {

    add_heap_tests_module();
    add_test_runner_tests_module();

    test_runner("*", "*");

    test_results_t results;
    aggregate_test_results(&results);

    fprintf(stderr, "\nTEST RESULTS: %ld PASSED, %ld FAILED, %ld SKIPPED", results.count_passed, results.count_failed, results.count_pending);

    return results.count_failed > 0 ? 1 : 0;
}