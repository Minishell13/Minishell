/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:31:50 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/12 18:21:14 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	here_doc(t_redir *redir)
{
	return (fork_heredoc(redir));
}

static int	count_heredocs(t_ast *node)
{
	if (!node)
		return (0);
	return (count_heredocs(node->child)
		+ (node->type == GRAM_HEREDOC)
		+ count_heredocs(node->sibling));
}

static t_bool	exec_heredocs(t_ast *node)
{
	if (!node)
		return (true);
	if (node->type == GRAM_HEREDOC)
	{
		if (here_doc(&node->u_data.redir) == false)
			return (false);
	}
	if (exec_heredocs(node->child) == false)
		return (false);
	if (exec_heredocs(node->sibling) == false)
		return (false);
	return (true);
}

t_bool	handle_heredocs(t_ast *root)
{
	int	total;

	if (!root)
		return (false);
	total = count_heredocs(root);
	if (total > 16)
	{
		fdprintf(STDERR_FILENO, HEREDOC_MAX, g_sh.shell);
		g_sh.exit_code = 2;
		return (false);
	}
	return (exec_heredocs(root));
}
