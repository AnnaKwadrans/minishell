# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 20:46:06 by akwadran          #+#    #+#              #
#    Updated: 2025/05/11 19:04:40 by kegonza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar -rcs
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRC = ${wildcard *.c}

OBJ = $(SRC:.c=.o)

SRC_BONUS = ft_list_bonus.c ft_list2_bonus.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

$(NAME): $(OBJ) $(OBJ_BONUS)
	$(LIB) $(NAME) $(OBJ) $(OBJ_BONUS)

.PHONY: all clean fclean re bonus

all: $(NAME)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all
	$(LIB) $(NAME) $(OBJ_BONUS)
