global ft_read
section .text

%ifdef LINUX
extern __errno_location
; ssize_t ft_read(int fd, void *buf, size_t count)
ft_read:
    mov     rax, 0              ; Linux SYS_read
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
ft_read:
    mov     rax, 0x2000003      ; macOS SYS_read
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
