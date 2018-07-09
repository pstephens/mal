#include "rt-funcs.h"
#include "rt-string.h"

void rt_filter(rt_filter_closure* context, void* item) {
    if (context->pred.fn(context->pred.context, item)) {
        context->next.fn(context->next.context, item);
    }
}

rt_transducer_closure* rt_make_filter(rt_filter_closure* context, rt_predicate_closure* pred,
                                      rt_transducer_closure* next) {
    rt_memzero(context, sizeof(rt_filter_closure));
    context->this.context = context;
    context->this.fn = (rt_transducer) rt_filter;
    context->pred = *pred;
    context->next = *next;
    return &context->this;
}