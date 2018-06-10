cmake_minimum_required(VERSION 3.10)
project(c-jit-x64 C ASM)

set(CMAKE_C_STANDARD 11)
enable_language(ASM_NASM)

add_executable(step0_repl step0_repl.c start.asm syscall.h syscall.asm linux-abi.h start.c io.c io.h stdlib.h stdlib.asm)
target_link_libraries(step0_repl -nostdlib)
