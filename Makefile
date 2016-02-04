# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 17:07:45 by ngrasset          #+#    #+#              #
#    Updated: 2016/02/04 06:06:08 by ngrasset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	21sh 

SRC =	main.c	tree_op.c	exec_tree.c		basic_parser.c	exec_node.c\
		lexer.c	token_matching.c			token_types.c

OBJ = $(SRC:.c=.o)

INCLUDES = -I./libft/includes -I./ft_readline/includes -I./includes

CFLAGS = -Wall -Wextra -Werror

LIBS = -L./libft -L./ft_readline -lft -lftrl -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	make -C ft_readline/
	gcc $(CFLAGS) $(LIBS) $^ -o $(NAME)

%.o: srcs/%.c
	gcc $(CFLAGS) $(INCLUDES) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
