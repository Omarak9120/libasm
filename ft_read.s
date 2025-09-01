global ft_read                      ; Export function name for linker to find
extern __errno_location             ; Import external function to get errno address

section .text                       ; Code section (executable instructions)
; ssize_t ft_read(int fd, void *buf, size_t count)
ft_read:                            ; Function entry point (label)
    mov     rax, 0                 ; rax = 0 (Linux syscall number for read)
    syscall                         ; Make system call (kernel function)
    cmp     rax, 0                 ; Compare return value with 0
    jl      .err_linux             ; If less than 0 (error), jump to error handler
    ret                            ; Success: return (rax contains bytes read)
.err_linux:                        ; Linux error handling (jump target)
    neg     rax                    ; rax = -rax (make positive for errno)
    mov     edi, eax               ; edi = errno value (parameter for __errno_location)
    call    __errno_location wrt ..plt  ; Get errno address (PIE-safe external call)
    mov     [rax], edi             ; Set errno = error value (store at returned address)
    mov     rax, -1                ; Return -1 (error indicator)
    ret

section .note.GNU-stack noalloc     ; Security: mark stack as non-executable
