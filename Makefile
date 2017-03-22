SRC = src/env.c
SRC += src/env_dot.c
SRC += src/flags.c
SRC += src/flags2.c
SRC += src/ft_printf.c
SRC += src/tools.c
SRC += src/tools2.c
SRC += src/print_all.c
SRC += src/print_char.c
SRC += src/print_wchar.c
SRC += src/print_str.c
SRC += src/print_wstr.c
SRC += src/print_number.c
NAME = libftprintf.a

OBJ = $(SRC:.c=.o)
FLAGS = -Werror -Wall -Wextra
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ) :
	@$(CC) -c $(FLAGS) -o $@ $*.c

clean :
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
