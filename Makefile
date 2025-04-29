NAME = minishell
RM = rm -f
CC = cc
FLAGS = -Werror -Wextra -Wall -fsanitize=address -g3
LIBFT_DIR = libft
LIBFT = libft/libft.a

# SRC = main.c printer.c lexer.c lexer_utils.c pipes_split.c
SRC = $(wildcard *.c)
SRC_AUX = ${wildcard aux/*.c}
SRC_LIBFT = ${wildcard libft/*.c}
SRC_ALL = $(SRC_AUX) $(SRC_LIBFT) $(SRC)

OBJ = $(SRC_ALL:.c=.o)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -Llibft -lft -lreadline
	touch .history

.PHONY:
	all re clean fclean

all: $(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all
