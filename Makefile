# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jraymond <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/19 15:26:12 by jraymond          #+#    #+#              #
#    Updated: 2020/02/07 19:11:28 by jraymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

FLAGS = -Wall -Wextra -Werror -shared

SRCS = ft_malloc.c \
       show_alloc_mem.c \
	   last_elem.c \
	   handle_large_block.c \
	   handle_tiny_small_block_bis.c \
	   ft_free_bis.c \
	   ft_realloc_bis.c \
	   request_block.c \
	   handle_defragmentation.c \
	   handle_free_chunk.c \
	   get_chunk.c \
	   print_showalloc.c \

OBJS = $(SRCS:.c=.o)

_GREEN=\x1b[32m
_RED=\x1b[31m
_END=\x1b[0m

all : $(NAME)

.PHONY : all fclean clean re

$(NAME) : $(OBJS)
		@make -C libft
		$(CC) -o $(NAME) $(FLAGS) $(OBJS) libft/libft.a
		ln -s $(NAME) libft_malloc.so

%.o : %.c
		@$(CC) -fPIC -c $^

clean :
		@make clean -C libft
		@rm -rf $(OBJS)
		@echo "$(_RED)clean : $(_GREEN)Done$(_END)"

fclean : clean
		@make fclean -C libft
		@rm -rf $(NAME)
		@rm -rf libft_malloc.so
		@echo "$(_RED)fclean : $(_GREEN)Done$(_END)"

re :
	@make fclean
	@make
