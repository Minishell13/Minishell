/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO: You need first to know the exact struct of AST tree
// TODO: The representation each node with his type and args
// TODO: How to parcoure throw this three and get nodes in the correct order
// TODO: Create functions for execution (per node type)
// TODO: Focus on execution flow, (memory, fds, error) management
// TODO: The leaks is fixed, now go and make behavioure like shell
// TODO: ...

void	run_executor(t_ast *node)
{
	switch (node->type)
	{
		case GRAM_COMPLETE_COMMAND:
			executor(node->child);
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

void executor(t_ast *node)
{
	t_fd_backup	backup;
	if (!node)
		return;
	save_fds(&backup);
	run_executor(node);
	restore_fds_backup(&backup);
}
