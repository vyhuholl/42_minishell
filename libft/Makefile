# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 10:00:43 by sghezn            #+#    #+#              #
#    Updated: 2020/04/30 05:54:54 by sghezn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INC = -I libft.h
FLAG = -Wall -Wextra -Werror

SRC = $(wildcard ft_*.c)
OBJ = $(SRC:%.c=%.o)
D_FILE = $(SRC:%.c=%.d)

all: $(OBJ) $(NAME)

%.o: %.c
	gcc $(FLAG) -O2 $(INC) -c $< -o $@ -MD

$(NAME): $(OBJ)
	ar rc $(NAME) $?
	ranlib $(NAME)

clean:
	rm -rf $(OBJ) $(D_FILE)

fclean: clean
	rm -rf $(NAME)

re: fclean all

include $(wildcard $(D_FILE))

.PHONY:	all clean fclean re
