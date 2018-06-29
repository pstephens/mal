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

add_executable(test_suite test/test-main.c ${stdlib_src} test/test-runner.c test/test-runner.h test/test-module-heap.c test/test-utils.c test/test-utils.h test/test-module-self.c test/test-assertions.c test/test-assertions.h test/test-model.c test/test-model.h test/lambda_test.c)

add_test(NAME test123 COMMAND test_suite a b c)