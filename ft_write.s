global ft_write
section .text

%ifdef LINUX
extern __errno_location
; ssize_t ft_write(int fd, const void *buf, size_t count)
ft_write:
    mov     rax, 1              ; Linux SYS_write
    syscall
    cmp     rax, 0
    jl      .err_linux
    ret
.err_linux:
    neg     rax                 ; rax = errno
    mov     edi, eax
    ; *** PIE-safe call via PLT ***
    call    __errno_location wrt ..plt
    mov     [rax], edi
    mov     rax, -1
    ret

%else                           ; macOS
extern ___error
ft_write:
    mov     rax, 0x2000004      ; macOS SYS_write
    syscall
    jc      .err_osx
    ret
.err_osx:
    mov     edi, eax
    call    ___error
    mov     [rax], edi
    mov     rax, -1
    ret
%endif

section .note.GNU-stack noalloc
