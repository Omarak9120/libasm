global  ft_strdup
extern  malloc
extern  ft_strlen

section .text
; char *ft_strdup(const char *s) ; rdi=s
ft_strdup:
    push    rdi                 ; save src

    ; len = ft_strlen(s) + 1
    call    ft_strlen
    inc     rax
    mov     rdi, rax            ; malloc(len)
    call    malloc
    test    rax, rax
    je      .malloc_fail

    ; copy using rcx index
    mov     rdx, rax            ; dst
    pop     rsi                 ; src
    xor     rcx, rcx
.copy:
    mov     r8b, [rsi + rcx]
    mov     [rdx + rcx], r8b
    inc     rcx
    test    r8b, r8b
    jne     .copy
    ; rax already = dst from malloc
    ret

.malloc_fail:
    pop     rdi                 ; balance stack
    xor     rax, rax            ; return NULL
    ret

section .note.GNU-stack noalloc
