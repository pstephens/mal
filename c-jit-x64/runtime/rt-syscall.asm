
section .text

;; long rt_syscall_write(unsigned int fd, const char* buff, size_t count);
;; ABI:
;;   fd -> rdi
;;   buff -> rsi
;;   count -> rdx
global rt_syscall_write
rt_syscall_write:
    mov rax, 1
    syscall
    ret

;; void rt_syscall_exit(int exit_code);
;; ABI:
;;   exit_code -> rdi
global rt_syscall_exit
rt_syscall_exit:
    mov rax, 60
    syscall
    ret

