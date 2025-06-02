/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:33:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 10:21:01 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- IO_REDIRECTION --------------------------------
int	parse_infile(t_redir *redir, t_gram type)
{
	int	fd;

	if (type == GRAM_HEREDOC)
		fd = here_doc(redir);
	else
		fd = open(redir->file, O_RDONLY);
	// if (fd < 0)
	// 	perror("sh_infile");
	return (fd);
}

int	parse_outfile(t_redir *redir, t_gram type)
{
	int	flags;
	int	fd;

	if (type == GRAM_REDIR_APPEND)
		flags = (O_WRONLY | O_CREAT | O_APPEND);
	else
		flags = (O_WRONLY | O_CREAT | O_TRUNC);
	fd = open(redir->file, flags, 0644);
	// if (fd < 0)
	// 	perror("sh_outfile");
	return (fd);
}

t_bool	redir(t_redir *r, t_gram type)
{
	int	fd;
	// 1) Handle input redirection: '<' or '<<'
	if (type == GRAM_REDIR_IN || type == GRAM_HEREDOC)
	{
		fd = parse_infile(r, type);
		if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
		{
			if (fd >= 0)
				close(fd);
			return (false);
		}
		close(fd);
	}
	// 2) Handle output redirection: '>' or '>>'
	else
	{
		fd = parse_outfile(r, type);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		{
			if (fd >= 0)
				close(fd);
			return (false);
		}
		close(fd);
	}
	return (true);
}

t_bool	expand_and_redir(t_ast *node)
{
	t_redir	*r;
	
	expand_redir(node);
	r = &node->u_data.redir;
	return (redir(r, node->type));
}

t_bool	execute_redirection(t_ast *node)
{
	t_ast 	*c;

	// 1. Do all other redirs (saving last in/out) exept heredocs
	c = node->child;
	while (c)
	{
		if (c->type != GRAM_HEREDOC && !expand_and_redir(c))
		{
			fdprintf(STDERR_FILENO, "minishell: %s: %s\n"
				, c->u_data.redir.file, strerror(errno));
			return (false);
		}
		c = c->sibling;
	}
	return (true);
}
