/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 06:41:45 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 06:14:35 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tosh.h>

t_shell		*g_shell = NULL;

int			init_shell(void)
{
	if (!(g_shell = malloc(sizeof(t_shell))))
		return (-1);
	g_shell->reader = ftrl_init();
	if (!g_shell->reader)
	{
		ft_putendl("Couldn't init ft_readline");
		return (-1);
	}
	if (ftrl_init_history(g_shell->reader, ".21sh_history") != 0)
	{
		ft_putendl("Couldn't load history");
		return (-1);
	}
	g_shell->running = 1;
	return (0);
}

void		destroy_shell(void)
{
	if (g_shell->reader)
	{
		ftrl_save_history(g_shell->reader);
		ftrl_exit(g_shell->reader);
	}
	free(g_shell);
}

void		debug_put_lexer(t_token *cur)
{
	if (!cur)
		return ;
	ft_putstr("TOKEN VALUE: ");
	if (cur->type == TOK_PIPE)
		ft_putstr("PIPE: ");
	if (cur->type == TOK_SEPARATOR)
		ft_putstr("SEPARATOR: ");
	if (cur->type == TOK_REDIR)
		ft_putstr("REDIR: ");
	if (cur->type == TOK_WORD)
		ft_putstr("WORD: ");
	if (cur->type == TOK_END_LIST)
	{
		ft_putstr("ENDLIST???\n");
		return ;
	}
	if (cur->type == TOK_INVALID)
	{
		ft_putstr("INVALID ?????\n");
		return ;
	}
	ft_putendl(cur->value);
	debug_put_lexer(cur->next);
}

int			main(void)
{
	t_lexer		*l;

	if (init_shell() != 0)
		return (1);
	l = create_lexer("/bin/echo lets go; ./proc_writer > redir_writer | ./proc_reader ; /bin/echo done");
	if (!l)
	{
		ft_putendl("Coulndt create lexer");
		return (0);
	}
	else
		debug_put_lexer(l->head_token);
	/*
	root = basic_parser("/bin/echo lets go; ./proc_writer > redir_writer | ./proc_reader ; /bin/echo done");
	debug_put_tree(root);
	ft_putendl("=========");
	exec_tree(root);
	line = "lol";
	while (ft_strcmp(line, "exit") != 0)
	{
		line = ft_readline(g_shell->reader, NULL);
		ft_putstr("\nReceived: ");
		ft_putendl(line);
	}
	*/
	destroy_shell();
	return (0);
}
