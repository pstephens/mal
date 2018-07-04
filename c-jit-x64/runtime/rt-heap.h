#ifndef RUNTIME_HEAP_H
#define RUNTIME_HEAP_H

#define RT_HEAP_DEFAULT_PAGESZ 4096

enum rt_heap_typetag {
    RT_HEAP_BOOL = 0,
    RT_HEAP_NUMBER = 1,
    RT_HEAP_STRING = 2,
    RT_HEAP_STRING_SPAN = 3,
    RT_HEAP_SYMBOL = 4,
    RT_HEAP_KEYWORD = 5,
    RT_HEAP_CONSCELL = 6,
    RT_HEAP_VECTOR = 7,
    RT_HEAP_VECTOR_SPAN = 8,
    RT_HEAP_VECTOR_LEAF = 9,
    RT_HEAP_MAP = 10,
    RT_HEAP_MAP_LEAF = 11,
    RT_HEAP_ATOM = 12,
    RT_HEAP_FUNC = 13,
    RT_HEAP_UDF = 14,
    RT_HEAP_MACRO = 15,
    RT_HEAP_ARRAY = 16,
};

typedef unsigned char rt_heap_typetag_t;
typedef unsigned char rt_heap_flags_t;
typedef unsigned int rt_heap_size_t;

typedef union {
    rt_heap_typetag_t subtype;
    unsigned short reserved;
} rt_heap_object_opt;

typedef struct {
    rt_heap_typetag_t typetag;
    rt_heap_flags_t flags;
    rt_heap_object_opt opt;
    rt_heap_size_t size;
} rt_heap_object_hdr;

typedef struct {
    void* base;
    void* next;             // address of next allocation
    void* commit;           // pages up to heap_commit have been set to PROT_READ|PROT_WRITE, pages after are PROT_NONE
    void* limit;            // heap_limit is just past the last usable page
    unsigned long pagesz;   // size of each virtual memory page
} rt_heap;

int rt_heap_init(rt_heap* heap, unsigned long pgsize, unsigned long maxheap);

void* rt_heap_alloc(rt_heap* heap, rt_heap_object_hdr spec);

#endif //RUNTIME_HEAP_H
