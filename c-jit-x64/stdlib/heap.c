#include "heap.h"
#include "stdlib.h"

static const long heap_size = 4L * 1024L * 1024L * 1024L;
static const long heap_align = 8L;
static void* heap_base;
static void* heap_next;     // address of next allocation
static void* heap_commit;   // pages up to heap_commit have been set to PROT_READ|PROT_WRITE, pages after are PROT_NONE
static void* heap_limit;    // heap_limit is just past the last usable page
static long heap_pagesz;    // size of each virtual memory page

void heap_init(long pgsize) {

}

void* heap_alloc(heap_object_hdr spec) {
    return NULL;
}
