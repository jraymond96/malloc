# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jraymond <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/19 15:26:12 by jraymond          #+#    #+#              #
#    Updated: 2019/12/02 19:27:46 by jraymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS = ft_malloc.c \
       show_alloc_mem.c \
	   last_elem.c \
	   handle_large_block.c \
	   handle_tiny_small_block.c \
	   ft_free.c \
	   request_block.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_strlen.c \
			ft_memccpy.c \
			ft_putstr.c \
			ft_putchar.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_mem2join.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strnstr.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_create_elem.c \
			ft_list_push_back.c \
			ft_list_push_front.c \
			ft_list_clear.c \
			ft_list_print.c \
			ft_strjoin_free.c \
			ft_lstaddback.c \
			ft_newbtree.c \
			ft_btreedel.c \
			ft_ilen.c \
			ft_btreeend.c \
			ft_lstrev.c \
			ft_lst_sort.c \
			ft_browsetree.c \
			ft_btreeinser.c \
			ft_get_opt.c \
			ft_btreelen.c \
			get_next_line.c \
			ft_lstrmelem.c \
			ft_memdup.c \
			ft_malloc.c \
			ft_memsplit.c \
			ft_strclen.c \
			ft_strmidjoin.c \

OBJS = $(SRCS:.c=.o)

_GREEN=\x1b[32m
_RED=\x1b[31m
_END=\x1b[0m

all : $(NAME)

.PHONY : all fclean clean re

$(NAME) : $(OBJS)
		$(CC) $(FLAGS) -c $(SRCS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)
		ln -s libft_malloc_$(HOSTTYPE).so libft_malloc.so


%.o : %.c
		@$(CC) $(FLAGS) -o $@ -c $^

clean :
		@rm -rf $(OBJS)
		@echo "$(_RED)clean : $(_GREEN)Done$(_END)"

fclean : clean
		@rm -rf $(NAME)
		@rm -rf libft_malloc.so
		@echo "$(_RED)fclean : $(_GREEN)Done$(_END)"

re :
	@make fclean
	@make
