global ft_strcmp
section .text
; int ft_strcmp(const char *s1, const char *s2) ; rdi=s1, rsi=s2
ft_strcmp:
    xor     rcx, rcx
.loop:
    mov     al, [rdi + rcx]
    mov     dl, [rsi + rcx]
    cmp     al, dl
    jne     .diff
    test    al, al
    je      .equal
    inc     rcx
    jmp     .loop
.diff:
    movzx   eax, al
    movzx   edx, dl
    sub     eax, edx            ; (unsigned char)s1[i] - (unsigned char)s2[i]
    ret
.equal:
    xor     eax, eax
    ret

section .note.GNU-stack noalloc
