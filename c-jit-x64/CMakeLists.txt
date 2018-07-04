cmake_minimum_required(VERSION 3.10)
project(c-jit-x64 C ASM)

enable_testing()

set(CMAKE_C_STANDARD 11)
enable_language(ASM_NASM)

include_directories(runtime)
include_directories(test-lib)

add_subdirectory(bootstrap)
add_subdirectory(runtime)
add_subdirectory(runtime-tests)
add_subdirectory(test-lib)
add_subdirectory(test-runner)

add_executable(step0_repl step0_repl.c)
target_link_libraries(step0_repl bootstrap runtime -nostdlib)

add_test(NAME test123 COMMAND test-runner a b c)
