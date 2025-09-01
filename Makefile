
NAME    = libasm.a
AS      = nasm
ASFLAGS = -f elf64
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
