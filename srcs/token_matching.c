/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_matching.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 06:02:10 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 06:05:44 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>

t_token_matcher		g_tok_matchers[] = {
	{TOK_PIPE, &is_token_pipe},
	{TOK_SEPARATOR, &is_token_separator}, 
	{TOK_REDIR, &is_token_redir},
	{TOK_WORD, &is_valid_word},
	{TOK_END_LIST, NULL}
};

int				is_token(char *str)
{
	int		i;

	i = 0;
	while (g_tok_matchers[i].type != TOK_END_LIST)
	{
		if (g_tok_matchers[i].matcher(str))
			return (1);
		i++;
	}
	return (0);
}

t_token_type	find_token_type(char *str)
{
	int		i;

	i = 0;
	while (g_tok_matchers[i].type != TOK_END_LIST)
	{
		if (g_tok_matchers[i].matcher(str))
			return (g_tok_matchers[i].type);
		i++;
	}
	return (TOK_INVALID);
}
