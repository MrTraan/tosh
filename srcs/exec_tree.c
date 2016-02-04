/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 07:27:07 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 03:41:11 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>
#include <sys/errno.h>
#include <debug.h>

int		is_pipe(char *str)
{
	return (ft_strcmp(str, "|") == 0);
}

int		is_semi_colon(char *str)
{
	return (ft_strcmp(str, ";") == 0);
}

int		simple_exec(char *cmd)
{
	char	**split;
	int		ret;
	pid_t	pid;

	ret = 0;
	split = ft_strsplit(cmd, ' ');
	pid = fork();
	if (pid == 0)
	{
		execve(*split, split, NULL);
		perror("Execve error");
	}
	else
		wait(&ret);
	ft_delstrtab(split);
	return (ret);
}

int		piped_node(t_tree_op *node)
{
	pid_t	l_pid;
	pid_t	r_pid;
	int		n;
	int		m;
	int		fd[2];

	pipe(fd);
	l_pid = fork();
	if (l_pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exit(exec_tree(node->left));
	}
	else
	{
		r_pid = fork();
		if (r_pid == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			exit(exec_tree(node->right));
		}
		else
		{
			n = wait(NULL);
			if (n == r_pid)
				close(fd[0]);
			else
				close(fd[1]);
			m = wait(NULL);
			if (m == l_pid)
				close(fd[1]);
			else
				close(fd[0]);
			debug_log("sub_process ended");
		}
	}
	return (0);
}

int		exec_tree(t_tree_op *node)
{
	if (!node)
		return (-1);
	if (node->type == NODE_EXPR)
		return (exec_node(node));
	if (node->type == NODE_OPERATOR && is_pipe(node->data))
		return (piped_node(node));
	if (node->type == NODE_OPERATOR && is_semi_colon(node->data))
	{
		exec_tree(node->left);
		exec_tree(node->right);
	}
	return (0);
}
