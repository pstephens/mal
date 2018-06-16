#include "startup.h"
#include "../stdlib/io.h"

extern int main(int argc, char**argv);

int start_system_init(int argc, char** argv, char** envp, auxv_t* auxv) {

    // TODO: Temporary, test env variable parameter
    for(int p = 0; *envp; ++envp, ++p) {
        put_string("envp ");
        put_long(p);
        put_string(": ");
        put_string(*envp);
        put_string("\n");
    }

    // TODO: Temporary, test auxv variable parameter
    for(int p = 0; auxv->a_type != AT_NULL; auxv++, p++) {
        put_string("auxv ");
        put_long(p);
        put_string(": ");
        switch(auxv->a_type) {
            case AT_IGNORE:
                put_string("AT_IGNORE");
                break;

            case AT_EXECFD:
                put_string("AT_EXECFD ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_PHDR:
                put_string("AT_PHDR ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_PHENT:
                put_string("AT_PHENT ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_PAGESZ:
                put_string("AT_PAGESZ ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_BASE:
                put_string("AT_BASE ");
                put_long(auxv->a_un.a_val);
                break;

            case AT_EXECFN:
                put_string("AT_EXECFN ");
                put_string(auxv->a_un.a_ptr);
                break;

            default:
                put_string("UNKNOWN ");
                put_long(auxv->a_type);
                put_string(" ");
                put_long(auxv->a_un.a_val);
                break;
        }
        put_string("\n");
    }

    return main(argc, argv);
}