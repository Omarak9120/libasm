global ft_strlen                    ; Export function name for linker to find
section .text                       ; Code section (executable instructions)
; size_t ft_strlen(const char *s) ; s in rdi, return in rax
ft_strlen:                         ; Function entry point (label)
    mov     rcx, 0                 ; rcx = 0 (initialize counter/index to 0)
.loop:                             ; Loop label (jump target)
    cmp     byte [rdi + rcx], 0    ; Compare: rdi[rcx] == 0? (check for null terminator)
    je      .end                    ; If equal (found null), jump to .end
    inc     rcx                     ; rcx++ (increment counter to next character)
    jmp     .loop                   ; Jump back to loop (unconditional jump)
.end:                              ; End label (jump target)
    mov     rax, rcx               ; rax = rcx (return counter value in rax)
    ret                             ; Return from function (rax contains length)

section .note.GNU-stack noalloc     ; Security: mark stack as non-executable 
