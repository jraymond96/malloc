# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jraymond <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/19 15:26:12 by jraymond          #+#    #+#              #
#    Updated: 2020/02/08 17:13:48 by jraymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TEST			=	a.out
NAME			=	libft_malloc_$(HOSTTYPE).so
LINK			=	libft_malloc.so
_SRCS			=	ft_malloc.c \
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


SRCS_DIR		=	srcs
SRCS			=	$(addprefix $(SRCS_DIR)/,$(_SRCS))

OBJS_DIR		=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/,$(_SRCS:%.c=%.o))

INCS_DIR		=	.
INCS			=	-I $(INCS_DIR) -I $(LIB_DIR)/includes
HEADER			=	$(INCS_DIR)/malloc.h

LIB_DIR			= libft

all: $(HEADER) $(NAME)

$(NAME): lib $(OBJS_DIR) $(OBJS)
		@$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L$(LIB_DIR) -lft -shared $(OBJS)
			ln -sf $(NAME) $(LINK)
		@echo "$(NAME) : Done"

$(OBJS_DIR):
		@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
		@$(CC) $(CFLAGS) -fPIC $(INCS) -c -o $@ $<

lib:
	@make -C $(LIB_DIR)



clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -rf $(OBJS_DIR)
		@echo "$(NAME) clean : Done"

fclean: clean
		@/bin/rm -f $(NAME) $(LINK) a.out
		@echo "$(NAME) fclean : Done"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
