#include "boot-startup.h"
#include "rt-io.h"

extern int main(int argc, char**argv);

int boot_system_init(int argc, char** argv, char** envp, auxv_t* auxv) {

    // TODO: Temporary, test-lib env variable parameter
    for(int p = 0; *envp; ++envp, ++p) {
        rt_put_string("envp ");
        rt_put_long(p);
        rt_put_string(": ");
        rt_put_string(*envp);
        rt_put_string("\n");
    }

    // TODO: Temporary, test-lib auxv variable parameter
    for(int p = 0; auxv->a_type != AT_NULL; auxv++, p++) {
        rt_put_string("auxv ");
        rt_put_long(p);
        rt_put_string(": ");
        switch(auxv->a_type) {
            case AT_IGNORE:
                rt_put_string("AT_IGNORE");
                break;

            case AT_EXECFD:
                rt_put_string("AT_EXECFD ");
                rt_put_long(auxv->a_un.a_val);
                break;

            case AT_PHDR:
                rt_put_string("AT_PHDR ");
                rt_put_long(auxv->a_un.a_val);
                break;

            case AT_PHENT:
                rt_put_string("AT_PHENT ");
                rt_put_long(auxv->a_un.a_val);
                break;

            case AT_PAGESZ:
                rt_put_string("AT_PAGESZ ");
                rt_put_long(auxv->a_un.a_val);
                break;

            case AT_BASE:
                rt_put_string("AT_BASE ");
                rt_put_long(auxv->a_un.a_val);
                break;

            case AT_EXECFN:
                rt_put_string("AT_EXECFN ");
                rt_put_string(auxv->a_un.a_ptr);
                break;

            default:
                rt_put_string("UNKNOWN ");
                rt_put_long(auxv->a_type);
                rt_put_string(" ");
                rt_put_long(auxv->a_un.a_val);
                break;
        }
        rt_put_string("\n");
    }

    return main(argc, argv);
}