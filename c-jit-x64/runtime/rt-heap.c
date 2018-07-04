#include "rt-heap.h"
#include "rt-stdlib.h"

static const unsigned long rt_heap_align = 8L;

static rt_heap rt_heap_default;

int rt_heap_init(rt_heap* heap, unsigned long pgsize, unsigned long maxheap) {
    return 1;
}

void* rt_heap_alloc(rt_heap* heap, rt_heap_object_hdr spec) {
    return NULL;
}
