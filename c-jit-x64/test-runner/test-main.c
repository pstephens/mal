#include <stdio.h>
#include "test-model.h"
#include "test-runner.h"
#include "rt-test-module-all.h"

int main(int argc, char** argv) {

    extern void lambda_test();

    lambda_test();

    test_modules_t* mods = test_new_modules();
    ADD_TEST_MODULE(mods, test_module_self);
    rt_register_test_modules(mods);

    test_runner(mods, "*", "*");

    test_results_t results;
    aggregate_test_results(mods, &results);
    fprintf(stderr, "\nTEST RESULTS: %ld PASSED, %ld FAILED, %ld SKIPPED\n",
            results.count_passed, results.count_failed, results.count_pending);

    return results.count_failed > 0 ? 1 : 0;
}