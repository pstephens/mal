#include <test-model.h>
#include <rt-stdlib.h>
#include <rt-funcs.h>
#include <test-assertions.h>

typedef struct {
    rt_transducer_closure this;
    int count;
    int last_item;
} filter_test_1_closure;

static void filter_test_1(filter_test_1_closure* context, const int* item) {
    context->count++;
    context->last_item = *item;
}

filter_test_1_closure filter_test_1_inst = {
        .this.context = &filter_test_1_inst,
        .this.fn = (rt_transducer) filter_test_1,
        .count = 0,
        .last_item = 0
};

static void reset_filter_test_1() {
    filter_test_1_inst.count = 0;
    filter_test_1_inst.last_item = 0;
}

static bool is_positive(void* context, const int* item) {
    return *item % 2 == 0 ? true : false;
}

DEFINE_TEST_INSTANCE(filter_test_1) {
    int nums[] = { 0, 1, 2, 3, 4, 5, 6 };

    // arrange
    rt_filter_closure filter;
    rt_predicate_closure pred = { .context = NULL, .fn = (rt_predicate) is_positive};
    rt_make_filter(&filter, &pred, &filter_test_1_inst.this);

    // test 1
    reset_filter_test_1();
    filter.this.fn(&filter, nums + 0);
    filter.this.fn(&filter, nums + 1);
    filter.this.fn(&filter, nums + 2);
    filter.this.fn(&filter, nums + 3);
    filter.this.fn(&filter, nums + 4);
    assert_signed_msg(filter_test_1_inst.count, EQ, 3, "(test 1, count)");
    assert_signed_msg(filter_test_1_inst.last_item, EQ, 4, "(test 1, last_item)");

    // test 2
    reset_filter_test_1();
    filter.this.fn(&filter, nums + 0);
    filter.this.fn(&filter, nums + 2);
    filter.this.fn(&filter, nums + 4);
    assert_signed_msg(filter_test_1_inst.count, EQ, 3, "(test 2, count)");
    assert_signed_msg(filter_test_1_inst.last_item, EQ, 4, "(test 2, last_item)");

    // test 3
    reset_filter_test_1();
    filter.this.fn(&filter, nums + 1);
    filter.this.fn(&filter, nums + 3);
    filter.this.fn(&filter, nums + 5);
    assert_signed_msg(filter_test_1_inst.count, EQ, 0, "(test 3, count)");
    assert_signed_msg(filter_test_1_inst.last_item, EQ, 0, "(test 3, last_item)");
}

DEFINE_TEST_MODULE(runtime_funcs) {
    ADD_TEST_INSTANCE(filter_test_1, NULL);
}
