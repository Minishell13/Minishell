/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/12 18:52:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	run_executor(t_ast *node)
{
	if (node->type == GRAM_COMPLETE_COMMAND)
		run_executor(node->child);
	else if (node->type == GRAM_OPERATOR_AND
		|| node->type == GRAM_OPERATOR_OR)
		execute_and_or(node);
	else if (node->type == GRAM_PIPE)
		execute_pipeline(node);
	else if (node->type == GRAM_IO_REDIRECT)
		execute_redirection(node);
	else if (node->type == GRAM_SIMPLE_COMMAND)
		execute_simple_cmd(node, false);
	else if (node->type == GRAM_SUBSHELL)
		execute_subshell(node);
}

t_bool	executor(t_ast *node)
{
	t_fd_backup	backup;

	if (!node)
		return (false);
	save_fds(&backup);
	if (handle_heredocs(g_sh.ast) == false)
		return (false);
	run_executor(node);
	restore_fds(backup.in, backup.out);
	return (true);
}
