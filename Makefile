# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 17:54:40 by hudescam          #+#    #+#              #
#    Updated: 2026/02/11 18:07:40 by hudescam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRC = lexer_helper.c lexer.c main.c parse_token.c \
		read_word.c signals.c syntax.c utils.c

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(READLINE) $(OBJ) $(LIBFT_A) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	
leaks: 
	$(MAKE)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp ./minishell

re: fclean all

.PHONY: all clean fclean re