/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 06:52:48 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/02 07:22:48 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>

t_tree_op		*new_node_op(char *data, t_node_type type)
{
	t_tree_op	*n;

	if (!(n = malloc(sizeof(t_tree_op))))
		return (NULL);
	n->data = data;
	n->type = type;
	n->left = NULL;
	n->right = NULL;
	return (n);
}

int			tree_add_elem(t_tree_op **root, t_tree_op *new)
{
	t_tree_op	*cur;

	if (!*root)
	{
		*root = new;
		return (1);
	}
	cur = *root;
	if ((cur->left && cur->left->type != NODE_EXPR) || (!cur->left))
	{
		if (tree_add_elem(&(cur->left), new))
			return (1);
	}
	return (tree_add_elem(&(cur->right), new));
}

void		debug_put_tree(t_tree_op *node)
{
	if (!node)
		return ;
	if (node->left)
		debug_put_tree(node->left);
	if (node->type == NODE_OPERATOR)
		ft_putstr("OP: ");
	ft_putendl(node->data);
	debug_put_tree(node->right);
}
