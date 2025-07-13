NAME = minishell
RM = rm -f
CC = cc
FLAGS_BASE = -Werror -Wextra -Wall 
# -g3
ifeq ($(SANITIZE),0)
	FLAGS = $(FLAGS_BASE)
else
	FLAGS = $(FLAGS_BASE) 
#-fsanitize=address
endif
LIBFT_DIR = libft
LIBFT = libft/libft.a

# Include readline library for macOS

UNAME_S := $(shell uname -s)
WHO := $(shell whoami)

ifeq ($(UNAME_S),Linux)
    FLAGS += -DLINUX_OS
endif
ifeq ($(UNAME_S),Darwin)
	ifeq ($(WHO),annakwadrans)
		READLINE_INC = -I/usr/local/opt/readline/include
		READLINE_LIB = -L/usr/local/opt/readline/lib
	else 
		READLINE_INC = -I/opt/homebrew/opt/readline/include
		READLINE_LIB = -L/opt/homebrew/opt/readline/lib
	endif
else
	READLINE_INC =
	READLINE_LIB =
endif

# SRC = main.c printer.c lexer.c lexer_utils.c pipes_split.c
SRC = $(wildcard *.c)
SRC_AUX = ${wildcard aux/*.c}
SRC_LIBFT = ${wildcard libft/*.c}
SRC_PARS = ${wildcard parser/*.c}
SRC_VARS = ${wildcard vars/*.c}
SRC_SIGNALS = ${wildcard signals/*.c}
SRC_EXEC = ${wildcard executor/*.c}
SRC_HERE_DOC = ${wildcard here_doc/*.c}
SRC_B_INS = buildins/ft_cd.c buildins/ft_exit.c buildins/ft_echo.c buildins/ft_pwd.c buildins/ft_env.c buildins/ft_export.c buildins/ft_unset.c

SRC_ALL = $(SRC_LIBFT) $(SRC_AUX) $(SRC_PARS) $(SRC_VARS) $(SRC_SIGNALS) $(SRC_EXEC) $(SRC_HERE_DOC) $(SRC_B_INS) $(SRC)

OBJ = $(SRC_ALL:.c=.o)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(FLAGS) $(READLINE_INC) $(OBJ) -o $(NAME) -Llibft -lft $(READLINE_LIB) -lreadline
	make clean
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
