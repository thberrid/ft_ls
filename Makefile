# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/29 19:26:47 by thberrid          #+#    #+#              #
#    Updated: 2020/01/05 11:05:52 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL	= /bin/sh
NAME	= ft_ls
DIR_C 	= srcs
DIR_O	= obj
DIR_H	= includes
NAME_C	= main.c \
			dir.c \
			dirlst.c \
			flags.c \
			list.c \
			options.c
NAME_O	= $(NAME_C:.c=.o)
NAME_H	= ft_ls.h
FILES_C	= $(addprefix $(DIR_C)/, $(NAME_C))
FILES_O	= $(addprefix $(DIR_O)/, $(NAME_O))
FILES_H	= $(addprefix $(DIR_H)/, $(NAME_H))
LIBFT	= ./libft/libft.a
FLAGS	= -Wall -Wextra -Werror -g3

all : $(NAME)

$(NAME) : $(FILES_O) $(FILES_H) $(LIBFT) $(MLX)
	gcc -I ./$(DIR_H) -I ./libft/includes -L ./libft/ -lft -o $(NAME) $(FILES_O)
#	gcc -fsanitize=address -I ./$(DIR_H) -I ./libft/includes -L ./libft/ -lft -o $(NAME) $(FILES_O)
 
$(DIR_O)/%.o : $(DIR_C)/%.c $(FILES_H)
	@ mkdir -p $(DIR_O)
	gcc $(FLAGS) -I ./$(DIR_H) -I ./libft/includes -c -o $@ $<
#	gcc $(FLAGS) -fsanitize=address -I ./$(DIR_H) -I ./libft/includes -c -o $@ $<

$(LIBFT) :
	make -C ./libft/

.PHONY : clean
clean :
	rm -f $(FILES_O)
	make -C ./libft fclean

.PHONY : fclean
fclean : clean
	rm -f $(NAME)

.PHONY : re
re : fclean all
