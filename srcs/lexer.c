/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 05:07:51 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 06:22:39 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>

t_lexer		*create_lexer(char *expr)
{
	t_lexer		*l;

	if (!(l = malloc(sizeof(t_lexer))))
		return (NULL);
	l->raw_expr = ft_strdup(expr);
	l->head_token = NULL;
	l->cur_token = NULL;
	if (lexer_parsing(l) != 0)
	{
		free(l->raw_expr);
		free(l);
		return (NULL);
	}
	return (l);
}

int			lexer_parsing(t_lexer *l)
{
	char	*ptr;
	int		i;

	ptr = l->raw_expr;
	while (*ptr)
	{
		i = 0;
		printf("parsing %s\n", ptr);
		while (ptr[i] && ptr[i] != ' ' && ptr[i] != '|' && ptr[i] != ';' && ptr[i] != '>')
			i++;
		if (i == 0)
			i++;
		if (create_new_token(l, ptr, i) != 0)
			return (-1);
		while (ptr[i] == ' ')
			i++;
		ptr += i;
	}
	return (0);
}

int			create_new_token(t_lexer *l, char *ptr, int i)
{
	t_token		*new_token;

	if (!(new_token = malloc(sizeof(t_token))))
		return (-1);
	printf("Creating token of value %s\n", ft_strsub(ptr, 0, i));
	if (!(new_token->value = ft_strsub(ptr, 0, i)))
	{
		free(new_token);
		return (-1);
	}
	new_token->type = find_token_type(new_token->value);
	new_token->next = NULL;
	lexer_push_token(l, new_token);
	return (0);
}

void		lexer_push_token(t_lexer *l, t_token *new)
{
	if (!l->cur_token)
	{
		l->head_token = new;
		l->cur_token = new;
		return ;
	}
	l->cur_token->next = new;
	l->cur_token = l->cur_token->next;
}
