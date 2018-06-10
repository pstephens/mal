
section .text

;; size_t strlen(const char* s);
;; ABI:
;;   s -> rdi
global strlen
strlen:
    ; scan string for '\0' string terminator
    mov rsi, rdi
    mov rcx, -1
    xor al, al
    repne scasb

    ; string size = rdi - rsi - 1
    mov rax, rdi
    sub rax, rsi
    dec rax
    ret
