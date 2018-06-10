
section .text

extern start_system_init
extern syscall_exit

global _start
_start:

    ; PER x86-64 Linux ABI https://github.com/hjl-tools/x86-psABI/wiki/x86-64-psABI-1.0.pdf
    ;
    ; | Purpose                    | Start Addr    | Length            |
    ; |----------------------------|---------------|-------------------|
    ; | Null aux vector entry      |               | 1 eightbyte       |
    ; | Aux vector entries ...     |               | 2 eightbytes each |
    ; | 0                          |               | 1 eightbyte       |
    ; | Environment pointers       |               | 1 eightbyte each  |
    ; | 0                          | 8+8*argc+rsp  | 1 eightbyte       |
    ; | Arg pointers               | 8+rsp         | argc eightbytes   |
    ; | Arg count                  | rsp           |                   |
    ; | ...                        |               |                   |
    ; |----------------------------|---------------|-------------------|

    xor rbp, rbp                     ; zero rbp per ABI

    mov r9, [rsp]                    ; int argc = *rsp
    lea rsi, [rsp + 8]               ; char** argv = rsp + 8
    lea rdx, [rsp + r9 * 8 + 16]     ; char** envp = rsp + argc * 8 + 16

    ; find the terminating null envp entry
    xor rax, rax
    mov rcx, -1
    mov rdi, rdx
    repne scasq
    mov rcx, rdi                     ; rcx is now at the start of auxv

    mov rdi, r9                      ; rdi is now argc

    ; int start_system_init(int argc, char** argv, char** envp, auxv_t* auxv)
    call start_system_init

    ; exit with the return from start_system_init
    mov rdi, rax
    call syscall_exit

    ret