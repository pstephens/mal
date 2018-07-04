add_library(runtime-tests test-module-heap.c)
target_link_libraries(runtime-tests runtime test-lib)