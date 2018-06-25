#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include "test-runner.h"
#include "test-utils.h"

typedef struct test_filter {
    const char* module_filter;
    const char* instance_filter;
} test_filter_t;

static void test_instance(test_filter_t* filter, test_instance_t* instance) {
    if(!wildcard_match(instance->parent->name, filter->module_filter) ||
            !wildcard_match(instance->name, filter->instance_filter)) {
        instance->state = TEST_PENDING;
        return;
    }

    print_instance_name(instance->parent, instance, "Testing ", ": ");
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
}

void test_runner(test_modules_t* mods, const char* module_filter, const char* instance_filter) {
    test_filter_t filter = { module_filter, instance_filter };

    enumerate_test_instances(mods, (test_instance_callback) test_instance, &filter);
}
