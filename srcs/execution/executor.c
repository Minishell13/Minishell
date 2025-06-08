/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 22:58:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	run_executor(t_ast *node)
{
	switch (node->type)
	{
		case GRAM_COMPLETE_COMMAND:
			run_executor(node->child);
			break;
		case GRAM_OPERATOR_AND:
		case GRAM_OPERATOR_OR:
			execute_and_or(node);
			break;
		case GRAM_PIPE:
			execute_pipeline(node);
			break;
		case GRAM_IO_REDIRECT:
			execute_redirection(node);
			break;
		case GRAM_SIMPLE_COMMAND:
			execute_simple_cmd(node, false);
			break;
		case GRAM_SUBSHELL:
			execute_subshell(node);
			break;
		default:
			break;
	}
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
