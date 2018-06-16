#ifndef C_JIT_X64_HEAP_H
#define C_JIT_X64_HEAP_H

#define HEAP_DEFAULT_PAGESZ 4096

enum heap_typetag {
    HEAP_BOOL = 0,
    HEAP_NUMBER = 1,
    HEAP_STRING = 2,
    HEAP_STRING_SPAN = 3,
    HEAP_SYMBOL = 4,
    HEAP_KEYWORD = 5,
    HEAP_CONSCELL = 6,
    HEAP_VECTOR = 7,
    HEAP_VECTOR_SPAN = 8,
    HEAP_VECTOR_LEAF = 9,
    HEAP_MAP = 10,
    HEAP_MAP_LEAF = 11,
    HEAP_ATOM = 12,
    HEAP_FUNC = 13,
    HEAP_UDF = 14,
    HEAP_MACRO = 15,
    HEAP_ARRAY = 16,
};

typedef unsigned char heap_typetag_t;
typedef unsigned char heap_flags_t;
typedef unsigned int heap_size_t;

typedef union {
    heap_typetag_t subtype;
    unsigned short reserved;
} heap_object_opt;

typedef struct {
    heap_typetag_t typetag;
    heap_flags_t flags;
    heap_object_opt opt;
    heap_size_t size;
} heap_object_hdr;

void heap_init(long pgsize);

void* heap_alloc(heap_object_hdr spec);

#endif //C_JIT_X64_HEAP_H
