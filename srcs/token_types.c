/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 05:59:02 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 06:01:59 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>

int		is_token_pipe(char *str)
{
	if (!str)
		return (0);
	if (*str == '|')
		return (1);
	return (0);
}

int		is_token_separator(char *str)
{
	if (!str)
		return (0);
	if (*str == ';')
		return (1);
	return (0);
}

int		is_token_redir(char *str)
{
	if (!str)
		return (0);
	if (*str == '>')
		return (1);
	return (0);
}

int		is_valid_word(char *str)
{
	if (!str)
		return (0);
	return (1);
}
