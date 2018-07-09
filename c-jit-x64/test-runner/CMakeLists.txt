include_directories(../runtime-tests)
add_executable(test-runner test-main.c)
target_link_libraries(test-runner test-lib runtime-tests)
