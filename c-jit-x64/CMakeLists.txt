cmake_minimum_required(VERSION 3.10)
project(c-jit-x64 C ASM)

set(CMAKE_C_STANDARD 11)
enable_language(ASM_NASM)

set(bootstrap_src
        bootstrap/startup.asm
        bootstrap/startup.c
        bootstrap/startup.h)

set(stdlib_src
        stdlib/heap.c
        stdlib/heap.h
        stdlib/io.c
        stdlib/io.h
        stdlib/stdlib.asm
        stdlib/stdlib.h
        stdlib/syscall.asm
        stdlib/syscall.h)

add_executable(step0_repl step0_repl.c ${bootstrap_src} ${stdlib_src})
target_link_libraries(step0_repl -nostdlib)

enable_testing()

add_executable(test_suite test/test-suite.c ${stdlib_src} test/test-runner.c test/test-runner.h test/heap-tests.c test/heap-tests.h)

add_test(NAME test123 COMMAND test_suite a b c)