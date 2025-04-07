RM = rm -f
CC = cc
FLAGS = -Werror -Wextra -Wall -fsanitize=address
NAME = minishell
LIBFT_DIR = libft
LIBFT = libft/libft.a

SRC = main.c printer.c lexer.c lexer_utils.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -Llibft -lft -lreadline

.PHONY:
	all re clean fclean

all: $(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all