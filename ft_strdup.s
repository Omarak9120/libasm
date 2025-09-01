global  ft_strdup                  ; Export function name for linker to find
extern  malloc                     ; Import external C function for memory allocation
extern  ft_strlen                  ; Import our function to get string length
extern  ft_strcpy                  ; Import our function to copy string

section .text                      ; Code section (executable instructions)
; char *ft_strdup(const char *s) ; rdi=s
ft_strdup:                         ; Function entry point (label)
    ; Check if s is NULL           ; Comment explaining next section
    test    rdi, rdi              ; Test if rdi == 0 (NULL pointer check)
    je      .return_null           ; If equal (NULL), jump to return NULL
    
    push    rdi                    ; Save source pointer on stack (preserve for later)

    ; len = ft_strlen(s) + 1      ; Comment explaining next section
    call    ft_strlen             ; Call our strlen function (result in rax)
    inc     rax                   ; rax++ (add 1 for null terminator)
    mov     rdi, rax              ; rdi = length (malloc parameter)
    call    malloc wrt ..plt      ; Call malloc (PIE-safe external call)
    test    rax, rax              ; Test if malloc returned NULL
    je      .malloc_fail           ; If NULL, jump to error handler

    ; Use ft_strcpy instead of manual copying  ; Comment explaining approach
    mov     rdi, rax              ; rdi = malloc result (destination for strcpy)
    pop     rsi                   ; rsi = original string (source for strcpy)
    call    ft_strcpy             ; Copy string using our function
    ; ft_strcpy returns dst, which is what we want  ; Comment explaining return
    ret                           ; Return (rax contains malloc'd string pointer)

.malloc_fail:                      ; Handle malloc failure (jump target)
    pop     rdi                   ; Restore stack balance (pop saved pointer)
    xor     rax, rax              ; rax = 0 (return NULL)
    ret

.return_null:                      ; Handle NULL input (jump target)
    xor     rax, rax              ; rax = 0 (return NULL)
    ret

section .note.GNU-stack noalloc    ; Security: mark stack as non-executable
