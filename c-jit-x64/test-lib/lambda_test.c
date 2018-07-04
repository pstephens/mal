#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

typedef struct thing thing_t;

struct thing {
    long num;
    int cnt;
    thing_t* children;
};

typedef bool (* fn_pred)(void* context, void* item);

typedef struct {
    void* context;
    fn_pred fn;
} lambda_pred;

typedef void (* fn_transducer)(void* context, void* item);

typedef struct {
    void* context;
    fn_transducer fn;
} lambda_transducer;

void foreach(thing_t* parent, lambda_transducer* next) {
    for (int i = 0; i < parent->cnt; ++i) {
        next->fn(next->context, parent->children + i);
    }
}

typedef struct {
    lambda_transducer this;
    lambda_transducer next;
    lambda_pred pred;
} lambda_filter;

void filter(lambda_filter* context, void* item) {
    if (context->pred.fn(context->pred.context, item)) {
        context->next.fn(context->next.context, item);
    }
}

lambda_transducer* make_filter(lambda_filter* context, lambda_pred* pred, lambda_transducer* next) {
    memset(context, 0, sizeof(lambda_filter));
    context->this.context = context;
    context->this.fn = (fn_transducer) filter;
    context->pred = *pred;
    context->next = *next;
    return &context->this;
}

typedef struct {
    lambda_transducer this;
    lambda_transducer next;
} lambda_flatten;

void flatten_things(lambda_flatten* context, thing_t* item) {
    if (item == NULL)
        return;

    context->next.fn(context->next.context, item);

    for (int i = 0; i < item->cnt; ++i) {
        flatten_things(context, item->children + i);
    }
}

lambda_transducer* make_flatten_things(lambda_flatten* context, lambda_transducer* next) {
    memset(context, 0, sizeof(lambda_flatten));
    context->this.context = context;
    context->this.fn = (fn_transducer) flatten_things;
    context->next = *next;
    return &context->this;
}

void print_thing(char* format, thing_t* item) {
    fprintf(stdout, format, item->num);
}

lambda_transducer* make_print_thing(lambda_transducer* lambda, char* format) {
    memset(lambda, 0, sizeof(lambda_transducer));
    lambda->context = format;
    lambda->fn = (fn_transducer) print_thing;
    return lambda;
}

bool thing_is_even(void* context, thing_t* thing) {
    return thing->num % 2 == 0 ? true : false;
}

static lambda_pred lambda_thing_is_even = {.context = NULL, .fn = (fn_pred) thing_is_even};

bool thing_is_odd(void* context, thing_t* thing) {
    return thing->num % 2 == 1 ? true : false;
}

static lambda_pred lambda_thing_is_odd = {.context = NULL, .fn = (fn_pred) thing_is_odd};

void lambda_test() {
    thing_t z[1] = {
            {.num = 243, .cnt = 0, .children = NULL}
    };

    thing_t y[2] = {
            {.num = 239, .cnt = 0, .children = NULL},
            {.num = 241, .cnt = 1, .children = z},
    };

    thing_t x[5] = {
            {.num =105, .cnt = 0, .children = NULL},
            {.num = 112, .cnt = 0, .children = NULL},
            {.num = 201, .cnt = 2, .children = y},
            {.num = 302, .cnt = 0, .children = NULL},
            {.num = 403, .cnt = 0, .children = NULL}
    };
    thing_t parent = {.num = 1, .cnt = 5, .children = x};

    lambda_transducer print_lambda;
    lambda_filter filter_lambda;
    lambda_flatten flatten_lambda;

    make_flatten_things(&flatten_lambda,
                        make_filter(&filter_lambda, &lambda_thing_is_odd,
                                    make_print_thing(&print_lambda, "-- %ld --\n")));

    flatten_things(&flatten_lambda, &parent);
}

#pragma clang diagnostic pop