/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:12:45 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 02:29:32 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>

t_tree_op	*basic_parser(char *expr)
{
	int			i;
	t_tree_op	*new_node;

	i = 0;
	printf("parsing expr %s\n", expr);
	if (ft_strchr(expr, ';') == NULL)
	{
		if (ft_strchr(expr, '|') == NULL)
			return (new_node_op(ft_strdup(expr), NODE_EXPR));
		while (expr[i] != '|')
			i++;
		new_node = new_node_op(ft_strdup("|"), NODE_OPERATOR);
		new_node->left = new_node_op(ft_strsub(expr, 0, i), NODE_EXPR);
		new_node->right = basic_parser(expr + i + 1);
		return (new_node);
	}
	while (expr[i] != ';')
		i++;
	new_node = new_node_op(ft_strdup(";"), NODE_OPERATOR);
	new_node->left = basic_parser(ft_strsub(expr, 0, i));
	new_node->right = basic_parser(expr + i + 1);
	return (new_node);
}
