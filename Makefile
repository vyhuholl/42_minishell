# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/22 18:30:52 by sghezn            #+#    #+#              #
#    Updated: 2020/05/10 01:34:34 by sghezn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INC = -I libft/libft.h -I get_next_line.h -I minishell.h
FLAG = -Wall -Wextra -Werror

SRC = 	builtin_cd.c \
		builtin_echo.c \
		builtin_env.c \
		builtin_exit.c \
		builtin_setenv.c \
		builtin_unsetenv.c \
		execute.c \
		expansions.c \
		get_next_line.c \
		main.c \
		util.c

OBJ = $(SRC:%.c=%.o)
D_FILE = $(SRC:%.c=%.d)

LIB_DIR = libft/
LIB = libft/libft.a

LIB_ALL = $(addsuffix .all,$(LIB_DIR))
LIB_CLEAN = $(addsuffix .clean,$(LIB_DIR))
LIB_FCLEAN = $(addsuffix .fclean,$(LIB_DIR))

all:	$(LIB_ALL) $(OBJ) $(NAME)

clean:	$(LIB_CLEAN)
	rm -rf $(OBJ) $(D_FILE)

fclean:	$(LIB_FCLEAN) clean
	rm -rf $(NAME)

re:	fclean all

%.o:	%.c
	gcc $(FLAG) -O2 -c $< -o $@ $(INC) -MD

$(NAME):	$(OBJ) $(LIB)
	gcc $(FLAG) $(OBJ) -o $(basename $(NAME)) $(LIB)

%.all:
	make -C $*

%.clean:
	make -C $* clean

%.fclean:
	rm -f $(addsuffix *.a,$*)

include $(wildcard $(D_FILE))

.PHONY:	all clean fclean re
