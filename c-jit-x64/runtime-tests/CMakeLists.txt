add_library(runtime-tests rt-test-module-heap.c rt-test-module-all.c rt-test-module-mem-ops.c rt-test-module-all.h rt-test-module-funcs.c)
target_link_libraries(runtime-tests runtime test-lib)