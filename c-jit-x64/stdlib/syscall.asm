
section .text

;; long syscall_write(unsigned int fd, const char* buff, size_t count);
;; ABI:
;;   fd -> rdi
;;   buff -> rsi
;;   count -> rdx
global syscall_write
syscall_write:
    mov rax, 1
    syscall
    ret

;; void syscall_exit(int exit_code);
;; ABI:
;;   exit_code -> rdi
global syscall_exit
syscall_exit:
    mov rax, 60
    syscall
    ret

