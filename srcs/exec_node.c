/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 03:30:37 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 03:46:24 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>
#include <debug.h>

int		has_redirection(char *cmd)
{
	return (ft_strchr(cmd, '>') != NULL);
}

int		parse_redirection(char *cmd)
{
	char	*redir;
	int		fd;
	char	debug[100];

	redir = ft_strchr(cmd, '>');
	if (!redir)
		return (1);
	*redir = '\0';
	redir = ft_strtrim(redir + 1);
	sprintf(debug, "opening %s for redirection\n", redir);
	debug_log(debug);	
	fd = open(redir, O_CREAT | O_TRUNC | O_RDWR, 0666);
	return (fd);
}

int		exec_node(t_tree_op *node)
{
	char	**split;
	pid_t	pid;
	int		ret;
	int		r_stdout;

	r_stdout = 1;
	if (has_redirection(node->data))
		r_stdout = parse_redirection(node->data);
	ret = 0;
	split = ft_strsplit(node->data, ' ');
	pid = fork();
	if (pid == 0)
	{
		dup2(r_stdout, 1);
		execve(*split, split, NULL);
		perror("Execve error");
		return (1);
	}
	else
		wait(&ret);
	if (r_stdout != 1)
		close(r_stdout);
	ft_delstrtab(split);
	return (ret);
}
