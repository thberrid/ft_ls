# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/17 17:15:46 by thberrid          #+#    #+#              #
#    Updated: 2019/11/20 02:28:08 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .c .o

AR = ar rc
VPATH = src
OBJDIR = obj

NAME = libft.a
SRCS = get_next_line.c \
	   print_memory.c \
 	   ft_addrswap.c \
	   ft_factorial.c \
	   ft_power.c \
 	   ft_sqrt.c \
	   ft_atoi.c \
	   ft_atol.c \
	   ft_bzero.c \
	   ft_intlen.c \
	   ft_isalnum.c \
	   ft_ischarset.c \
	   ft_isalpha.c \
	   ft_isascii.c \
	   ft_isdigit.c \
	   ft_isspace.c \
	   ft_isprint.c \
	   ft_itoa.c \
	   ft_lstadd.c \
	   ft_lstgetlast.c \
	   ft_lstgetn.c \
	   ft_lstappend.c \
	   ft_lstlen.c \
	   ft_lstpush.c \
	   ft_lstpop.c \
	   ft_lstdel.c \
	   ft_lstdelone.c \
 	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_lstnew.c \
	   ft_lstremove.c \
	   ft_memalloc.c \
	   ft_memccpy.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memcpy.c \
	   ft_memdel.c \
	   ft_memerase.c \
	   ft_memmove.c \
	   ft_memrealloc.c \
	   ft_memset.c \
	   ft_memswap.c \
	   ft_putascii.c \
	   ft_putchar.c \
	   ft_putchar_fd.c \
	   ft_putfloat.c \
	   ft_putendl.c \
	   ft_putendl_fd.c \
	   ft_putnbr.c \
	   ft_putnbr_fd.c \
	   ft_putstr.c \
	   ft_putstr_fd.c \
	   ft_strcat.c \
	   ft_strchr.c \
	   ft_strclr.c \
	   ft_strcmp.c \
	   ft_strcpy.c \
	   ft_strdel.c \
	   ft_strdup.c \
	   ft_strequ.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strjoin.c \
	   ft_strlcat.c \
	   ft_strlen.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_strncat.c \
	   ft_strncmp.c \
	   ft_strncpy.c \
	   ft_strnequ.c \
	   ft_strnew.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strsplit.c \
	   ft_strsplitspaces.c \
	   ft_strstr.c \
	   ft_strsub.c \
	   ft_strtrim.c \
	   ft_tolower.c \
	   ft_toupper.c
INC_NAME 	= libft.h \
			  get_next_line.h
CPPFLAGS 	= -I ./includes
INCDIR 		= includes
CPPFLAGS 	= -I ./includes
CFLAGS		= -Wall -Wextra -Werror -g3
OBJS_NAME 	= $(SRCS:.c=.o)
OBJS 		= $(addprefix $(OBJDIR)/, $(OBJS_NAME))
FILES_H 	= $(addprefix $(INCDIR)/, $(INC_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^
	ranlib $@

$(OBJDIR)/%.o: %.c $(FILES_H) | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir $@

.PHONY: clean
clean: 
	$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
