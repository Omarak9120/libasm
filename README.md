# Libasm Project Guide

## Project Overview
**Goal**: Become familiar with x86-64 assembly language by implementing standard C library functions in assembly.

**Library Name**: `libasm.a`

---

## Technical Requirements

### Assembly Constraints
- **Architecture**: 64-bit x86-64 assembly
- **Assembler**: NASM (Netwide Assembler)
- **Syntax**: Intel syntax (NOT AT&T)
- **File Extension**: `.s` files (no inline ASM)
- **Calling Convention**: x86-64 System V ABI
- **Compilation Flag**: `-no-pie` is **FORBIDDEN**

### Build System
Your Makefile must include:
- `$(NAME)` - Build the library
- `all` - Default target
- `clean` - Remove object files
- `fclean` - Remove object files and library
- `re` - Rebuild everything
- `bonus` - Build bonus functions (separate from mandatory)

### Error Handling
- Must check for errors during syscalls
- Must set `errno` properly
- Allowed to call: `__error` or `errno_location` (platform-dependent)

---

## Mandatory Part

### Functions to Implement

#### 1. `ft_strlen`
```c
size_t ft_strlen(const char *s);
```
- Calculate the length of a string
- Reference: `man 3 strlen`

#### 2. `ft_strcpy`
```c
char *ft_strcpy(char *dst, const char *src);
```
- Copy a string from src to dst
- Reference: `man 3 strcpy`

#### 3. `ft_strcmp`
```c
int ft_strcmp(const char *s1, const char *s2);
```
- Compare two strings lexicographically
- Reference: `man 3 strcmp`

#### 4. `ft_write`
```c
ssize_t ft_write(int fd, const void *buf, size_t count);
```
- Write to a file descriptor
- Reference: `man 2 write`
- **Must handle errno on error**

#### 5. `ft_read`
```c
ssize_t ft_read(int fd, void *buf, size_t count);
```
- Read from a file descriptor
- Reference: `man 2 read`
- **Must handle errno on error**

#### 6. `ft_strdup`
```c
char *ft_strdup(const char *s);
```
- Duplicate a string (allocate memory)
- Reference: `man 3 strdup`
- **Can call `malloc`**
- **Must handle errno on malloc failure**

---