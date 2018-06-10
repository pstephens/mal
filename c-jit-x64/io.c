#include "io.h"
#include "stdlib.h"

void puts(const char* s) {
    size_t len = strlen(s);
    syscall_write(0, s, len);
}

void put_long(long v) {
    char buff[21];
    char* s = &buff[20];
    int neg = v < 0 ? 1 : 0;
    if(neg) {
        v = -v;
    }

    *s-- = 0;
    if(v == 0) {
        *s-- = '0';
    } else {
        while(v != 0L) {
            *s-- = (char)('0' + (v % 10L));
            v = v / 10L;
        }

        if(neg) {
            *s-- = '-';
        }
    }

    puts(s + 1);
}