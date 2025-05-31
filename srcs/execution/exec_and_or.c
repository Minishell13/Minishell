/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 19:10:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO The heredoc must be restored or somting if it is attached with &&, ||

//* -------------------------------- AND_OR --------------------------------
void	and_or_wrapper(t_ast *root, t_ast *node)
{
	sh.in = track_dup(STDIN_FILENO);
	sh.out = track_dup(STDOUT_FILENO);
	executor(root, node);
	// Restore in case redirection happened
	restore_fds(sh.in, sh.out);
}

void	execute_and_or(t_ast *root, t_ast *node)
{
	// Also Restore in case redirection happened
	and_or_wrapper(root, node->child);
	if (node->type == GRAM_OPERATOR_AND && sh.exit_code == 0)
		and_or_wrapper(root, node->child->sibling);
	else if (node->type == GRAM_OPERATOR_OR && sh.exit_code != 0)
		and_or_wrapper(root, node->child->sibling);
}
