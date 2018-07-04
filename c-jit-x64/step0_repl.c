#include "rt-syscall.h"
#include "rt-io.h"
#include "rt-heap.h"

int main(int argc, char* argv[]) {
    char x[] = "Hello, World\n";
    rt_syscall_write(0, x, sizeof(x) - 1);

    int y = sizeof(rt_heap_object_hdr);
    rt_put_string("heap_object_hdr: ");
    rt_put_long(y);
    rt_put_string("\n");


    //heap_object_hdr xx = ;
    //heap_alloc((heap_object_hdr){.typetag = HEAP_ARRAY, .size = 55});

    // TODO: Temporary, test-lib argc parameter
    rt_put_string("argc: ");
    rt_put_long(argc);
    rt_put_string("\n");

    // TODO: Temporary, test-lib argv parameter
    for(int i = 0; i < argc; ++i) {
        rt_put_string("argv ");
        rt_put_long(i);
        rt_put_string(": ");
        rt_put_string(argv[i]);
        rt_put_string("\n");
    }

    return 17;
}