# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 20:46:06 by akwadran          #+#    #+#              #
#    Updated: 2025/02/12 20:41:28 by akwadran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar -rcs
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRC = ft_ctype.c ft_ctype2.c ft_put.c ft_stdlib.c ft_str.c ft_str2.c ft_str3.c \
	ft_string.c ft_string2.c ft_string3.c get_next_line.c get_next_line_utils.c \
	ft_printf.c ft_printf_utils.c ft_putnbr.c ft_putnbr_uns.c ft_puthexa.c

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
