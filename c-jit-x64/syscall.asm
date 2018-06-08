
    section .text

global syscall_exit
syscall_exit:

    mov rax, 60
    syscall
    ret

global syscall_write
syscall_write:
    mov rax, 1
    syscall
    ret
