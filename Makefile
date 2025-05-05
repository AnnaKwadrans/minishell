NAME = minishell
RM = rm -f
CC = cc
FLAGS = -Werror -Wextra -Wall -fsanitize=address -g3
LIBFT_DIR = libft
LIBFT = libft/libft.a

# Include readline library for macOS

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	READLINE_INC = -I/opt/homebrew/opt/readline/include
	READLINE_LIB = -L/opt/homebrew/opt/readline/lib
else
	READLINE_INC =
	READLINE_LIB =
endif

# SRC = main.c printer.c lexer.c lexer_utils.c pipes_split.c
SRC = $(wildcard *.c)
SRC_AUX = ${wildcard aux/*.c}
SRC_LIBFT = ${wildcard libft/*.c}
SRC_ALL = $(SRC_AUX) $(SRC_LIBFT) $(SRC)

OBJ = $(SRC_ALL:.c=.o)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(FLAGS) $(READLINE_INC) $(OBJ) -o $(NAME) -Llibft -lft $(READLINE_LIB) -lreadline
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
