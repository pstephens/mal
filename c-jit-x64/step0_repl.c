#include "stdlib/syscall.h"
#include "stdlib/io.h"
#include "stdlib/heap.h"

int main(int argc, char* argv[]) {
    char x[] = "Hello, World\n";
    syscall_write(0, x, sizeof(x) - 1);

    int y = sizeof(heap_object_hdr);
    put_string("heap_object_hdr: ");
    put_long(y);
    put_string("\n");


    //heap_object_hdr xx = ;
    //heap_alloc((heap_object_hdr){.typetag = HEAP_ARRAY, .size = 55});

    // TODO: Temporary, test argc parameter
    put_string("argc: ");
    put_long(argc);
    put_string("\n");

    // TODO: Temporary, test argv parameter
    for(int i = 0; i < argc; ++i) {
        put_string("argv ");
        put_long(i);
        put_string(": ");
        put_string(argv[i]);
        put_string("\n");
    }

    return 17;
}