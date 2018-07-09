#ifndef RUNTIME_FUNCS_H
#define RUNTIME_FUNCS_H

#include <stdbool.h>

typedef bool (* rt_predicate)(void* context, void* item);

typedef struct {
    void* context;
    rt_predicate fn;
} rt_predicate_closure;

typedef void (* rt_transducer)(void* context, void* item);

typedef struct {
    void* context;
    rt_transducer fn;
} rt_transducer_closure;

typedef struct {
    rt_transducer_closure this;
    rt_transducer_closure next;
    rt_predicate_closure pred;
} rt_filter_closure;

void rt_filter(rt_filter_closure* context, void* item);
rt_transducer_closure* rt_make_filter(rt_filter_closure* context, rt_predicate_closure* pred,
                                      rt_transducer_closure* next);


#endif //RUNTIME_FUNCS_H
