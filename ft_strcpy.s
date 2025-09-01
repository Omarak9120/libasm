global ft_strcpy                    ; Export function name for linker to find
section .text                       ; Code section (executable instructions)
; char *ft_strcpy(char *dst, const char *src) ; rdi=dst, rsi=src, ret=dst
ft_strcpy:                         ; Function entry point (label)
    mov     rax, rdi              ; rax = rdi (save destination pointer for return)
    xor     rcx, rcx              ; rcx = 0 (index counter, xor is faster than mov)
    
.copy_loop:                       ; Copy loop label (jump target)
    mov     dl, [rsi + rcx]       ; dl = src[index] (load byte from source string)
    mov     [rdi + rcx], dl       ; dst[index] = dl (store byte to destination string)
    inc     rcx                   ; index++ (increment counter to next character)
    test    dl, dl                ; Test if dl == 0 (check for null terminator)
    jne     .copy_loop            ; If not equal (not null), jump back to loop
    
    ret                           ; Return (rax already contains dst pointer)

section .note.GNU-stack noalloc     ; Security: mark stack as non-executable
