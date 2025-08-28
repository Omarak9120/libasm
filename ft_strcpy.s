global ft_strcpy
section .text
; char *ft_strcpy(char *dst, const char *src) ; rdi=dst, rsi=src, ret=dst
ft_strcpy:
    mov     rax, rdi
    xor     rcx, rcx
.copy:
    mov     dl,  [rsi + rcx]
    mov     [rdi + rcx], dl
    inc     rcx
    test    dl, dl
    jne     .copy
    ret

section .note.GNU-stack noalloc
