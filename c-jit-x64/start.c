#include "linux-abi.h"
#include "io.h"

extern int main(int argc, char**argv);

int start_system_init(int argc, char** argv, char** envp, auxv_t* auxv) {

    // TODO: Temporary, test env variable parameter
    for(int p = 0; *envp; ++envp, ++p) {
        puts("envp ");
        put_long(p);
        puts(": ");
        puts(*envp);
        puts("\n");
    }

    // TODO: Temporary, test auxv variable parameter
    for(int p = 0; auxv->a_type != AT_NULL; auxv++, p++) {
        puts("auxv ");
        put_long(p);
        puts(": ");
        switch(auxv->a_type) {
            case AT_IGNORE:
                puts("AT_IGNORE");
                break;

            case AT_EXECFD:
                puts("AT_EXECFD ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_PHDR:
                puts("AT_PHDR ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_PHENT:
                puts("AT_PHENT ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_PAGESZ:
                puts("AT_PAGESZ ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_BASE:
                puts("AT_BASE ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_EXECFN:
                puts("AT_EXECFN ");
                puts(auxv->a_un.a_ptr);
                break;

            default:
                puts("UNKNOWN ");
                put_long(auxv->a_type);
                puts(" ");
                put_long(auxv->a_un.a_val);
                break;
        }
        puts("\n");
    }

    return main(argc, argv);
}