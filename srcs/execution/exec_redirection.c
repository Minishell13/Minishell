/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:33:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 12:59:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// //* -------------------------------- IO_REDIRECTION --------------------------------
int	parse_infile(t_redir *redir, t_gram type)
{
	int	fd;

	if (type == GRAM_HEREDOC)
		here_doc(redir);
	fd = open(redir->file, O_RDONLY);
	if (fd < 0 || check_access(redir->file, (R_OK | F_OK)) == false)
		perror("sh_infile");
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
	if (fd < 0 || check_access(redir->file, W_OK) == false)
		perror("sh_outfile");
	return (fd);
}

void	redir(t_redir *r, t_gram type)
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
			return ;
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
			return ;
		}
		close(fd);
	}	
}

void	expand_and_redir(t_ast *node)
{
	t_redir	*r;
	
	expand_redir(node);
	r = &node->data.redir;
	redir(r, node->type);
}

void	execute_redirection(t_ast *node)
{
	t_ast 	*c;

	// 1. Do all other redirs (saving last in/out) exept heredocs
	c = node->child;
	while (c)
	{
		if (c->type != GRAM_HEREDOC)
			expand_and_redir(c);
		c = c->sibling;
	}
}
