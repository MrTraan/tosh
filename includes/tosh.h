/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 06:38:56 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 06:08:58 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOSH_H
# define TOSH_H
# include <stdlib.h>
# include <unistd.h>
# include <ft_readline.h>
# include <libft.h>

typedef struct			s_shell
{
	int					running;
	t_rl_reader			*reader;
}						t_shell;

extern t_shell			*g_shell;

typedef enum			e_node_type
{
	NODE_OPERATOR,
	NODE_EXPR
}						t_node_type;

typedef struct			s_tree_op
{
	t_node_type			type;
	char				*data;
	struct s_tree_op	*left;
	struct s_tree_op	*right;
}						t_tree_op;

typedef enum			e_token_type
{
	TOK_PIPE,
	TOK_SEPARATOR,
	TOK_REDIR,
	TOK_WORD,
	TOK_END_LIST,
	TOK_INVALID
}						t_token_type;

typedef struct			s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct			s_token_matcher
{
	t_token_type		type;
	int					(*matcher)(char *);
}						t_token_matcher;

typedef struct			s_lexer
{
	char				*raw_expr;
	t_token				*head_token;
	t_token				*cur_token;
}						t_lexer;

t_tree_op				*new_node_op(char *data, t_node_type type);
int						tree_add_elem(t_tree_op **root, t_tree_op *new);
void					debug_put_tree(t_tree_op *node);

int						exec_tree(t_tree_op *node);

t_tree_op				*basic_parser(char *expr);

int						exec_node(t_tree_op *node);

t_lexer					*create_lexer(char *expr);
int						lexer_parsing(t_lexer *l);
int						create_new_token(t_lexer *l, char *ptr, int i);
void					lexer_push_token(t_lexer *l, t_token *new);

int						is_token(char *str);
t_token_type			find_token_type(char *str);
int						is_token_pipe(char *str);
int						is_token_separator(char *str);
int						is_token_redir(char *str);
int						is_valid_word(char *str);
#endif
