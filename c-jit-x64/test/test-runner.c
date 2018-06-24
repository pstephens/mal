#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include "test-runner.h"
#include "test-utils.h"

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
        if(0 == waitid(P_PID, (id_t) pid, &info, (unsigned)WEXITED | (unsigned)WSTOPPED)) {
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

static void test_module(test_module_t* mod, const char* instance_filter) {
    test_instance_t* instance = mod->first_instance;
    while(instance != NULL) {
        if(wildcard_match(instance->name, instance_filter))
            test_instance(mod, instance);

        instance = instance->next;
    }
}

void test_runner(test_modules_t* mods, const char* module_filter, const char* instance_filter) {
    test_module_t *mod = mods->first;
    while (mod != NULL) {
        if(wildcard_match(mod->name, module_filter))
            test_module(mod, instance_filter);

        mod = mod->next;
    }
}
