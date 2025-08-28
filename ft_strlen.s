global ft_strlen
section .text
; size_t ft_strlen(const char *s) ; s in rdi, return in rax
ft_strlen:
    mov     rcx, 0
.loop:
    cmp     byte [rdi + rcx], 0
    je      .end
    inc     rcx
    jmp     .loop
.end:
    mov     rax, rcx
    ret
