UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    NASM_FMT = macho64
    OSFLAG   = -DOSX
else
    NASM_FMT = elf64
    OSFLAG   = -DLINUX
endif

NAME    = libasm.a
AS      = nasm
ASFLAGS = -f $(NASM_FMT) $(OSFLAG)
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJ = $(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^

%.o: %.s
	@$(AS) $(ASFLAGS) $< -o $@

test: all
	$(CC) $(CFLAGS) -I. main.c -L. -lasm -o tester

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME) tester

re: fclean all

.PHONY: all clean fclean re test
