#include "syscall.h"
#include "io.h"

int main(int argc, char* argv[]) {
    char x[] = "Hello, World\n";
    syscall_write(0, x, sizeof(x) - 1);


    // TODO: Temporary, test argc parameter
    puts("argc: ");
    put_long(argc);
    puts("\n");

    // TODO: Temporary, test argv parameter
    for(int i = 0; i < argc; ++i) {
        puts("argv ");
        put_long(i);
        puts(": ");
        puts(argv[i]);
        puts("\n");
    }

    return 17;
}