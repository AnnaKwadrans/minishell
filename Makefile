NAME = minishell
RM = rm -f
CC = cc
FLAGS_BASE = -Werror -Wextra -Wall -g3

ifeq ($(SANITIZE),0)
FLAGS = $(FLAGS_BASE)
else
FLAGS = $(FLAGS_BASE) -g -fsanitize=address
endif

# Feature test macros
FLAGS += -D_POSIX_C_SOURCE=200909L

UNAME_S := $(shell uname -s)
WHO := $(shell whoami)

ifeq ($(UNAME_S),Linux)
FLAGS += -D_GNU_SOURCE
endif

# Readline library configuration
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

LIBFT_DIR = libft
LIBFT = libft/libft.a

SRC = main.c

SRC_AUX = aux/array_functions.c\
	aux/ft_full_split.c

SRC_LIBFT = libft/ft_ctype.c\
	libft/ft_ctype2.c\
	libft/ft_list_bonus.c\
	libft/ft_list2_bonus.c\
	libft/ft_printf_utils.c\
	libft/ft_printf.c\
	libft/ft_put.c\
	libft/ft_puthexa.c\
	libft/ft_putnbr_uns.c\
	libft/ft_stdlib.c\
	libft/ft_str.c\
	libft/ft_str2.c\
	libft/ft_str3.c\
	libft/ft_strcmp.c\
	libft/ft_string.c\
	libft/ft_string2.c\
	libft/ft_string3.c\
	libft/get_next_line_utils.c\
	libft/get_next_line.c

SRC_BUILDINS =	buildins/ft_cd.c\
	buildins/ft_echo.c\
	buildins/ft_env.c\
	buildins/ft_exit.c\
	buildins/ft_export1.c\
	buildins/ft_export2.c\
	buildins/ft_pwd.c\
	buildins/ft_unset.c

SRC_EXEC = executor/exec_builtin.c\
	executor/exec_cmd_paths.c\
	executor/exec_cmd.c\
	executor/executor.c\
	executor/infile.c\
	executor/outfile.c\
	executor/redirect.c

SRC_HERE_DOC = here_doc/aux.c\
	here_doc/buffer.c\
	here_doc/check.c\
	here_doc/cmd.c\
	here_doc/delimeter.c\
	here_doc/here_doc.c\
	here_doc/outfiles.c

SRC_PARS = parser/cleanup.c\
	parser/command_utils.c\
	parser/command.c\
	parser/data.c\
	parser/parser_utils.c\
	parser/parser.c\
	parser/pipes_split.c\
	parser/quotes.c\
	parser/validator.c

SRC_SIGNALS = signals/here_doc.c\
	signals/sigint.c\
	signals/signals.c\
	signals/sigquit.c

SRC_VARS = vars/aux.c\
	vars/counts1.c\
	vars/counts2.c\
	vars/crud1.c\
	vars/crud2.c\
	vars/search.c\
	vars/varenv1.c\
	vars/varenv2.c

# SRC_ALL := \
#     $(SRC) \
#     $(addprefix aux/,       $(AUX_SRCS))       \
#     $(addprefix libft/,     $(LIBFT_SRCS))     \
#     $(addprefix buildins/,  $(BUILDINS_SRCS))  \
#     $(addprefix executor/,  $(EXEC_SRCS))      \
#     $(addprefix here_doc/,  $(HERE_DOC_SRCS))  \
#     $(addprefix parser/,    $(PARS_SRCS))      \
#     $(addprefix signals/,   $(SIGNALS_SRCS))   \
#     $(addprefix vars/,      $(VARS_SRCS))

SRC_ALL = $(SRC) $(SRC_AUX) $(SRC_LIBFT) $(SRC_BUILDINS) $(SRC_EXEC) $(SRC_HERE_DOC) $(SRC_PARS) $(SRC_SIGNALS) $(SRC_VARS)

OBJ = $(SRC_ALL:.c=.o)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(FLAGS) $(READLINE_INC) $(OBJ) -o $(NAME) -Llibft -lft $(READLINE_LIB) -lreadline
	make clean

.PHONY: all re clean fclean

all: $(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all
