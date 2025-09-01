global ft_strcmp                    ; Export function name for linker to find
section .text                       ; Code section (executable instructions)
; int ft_strcmp(const char *s1, const char *s2) ; rdi=s1, rsi=s2
ft_strcmp:                         ; Function entry point (label)
    xor     rcx, rcx              ; rcx = 0 (index counter, xor is faster than mov)
.loop:                             ; Main comparison loop label (jump target)
    mov     al, [rdi + rcx]       ; al = s1[index] (load byte from first string)
    mov     dl, [rsi + rcx]       ; dl = s2[index] (load byte from second string)
    cmp     al, dl                ; Compare: al - dl (set flags for conditional jump)
    jne     .diff                  ; If not equal, jump to difference handling
    test    al, al                ; Test if al == 0 (check for null terminator)
    je      .equal                 ; If null found, strings are equal
    inc     rcx                   ; index++ (move to next character)
    jmp     .loop                 ; Jump back to loop (unconditional jump)
.diff:                             ; Handle difference found (jump target)
    cmp     al, dl                ; Compare again: al - dl (set flags)
    jl      .less                  ; If al < dl, jump to .less (s1 < s2)
    mov     eax, 1                ; al > dl, return 1 (s1 > s2)
    ret
.less:                             ; Handle s1 < s2 (jump target)
    mov     eax, -1               ; Return -1 (s1 < s2)
    ret
.equal:                            ; Handle strings equal (jump target)
    xor     eax, eax              ; eax = 0 (return 0 for equal strings)
    ret

section .note.GNU-stack noalloc     ; Security: mark stack as non-executable
