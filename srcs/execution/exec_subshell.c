/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/01 14:56:29 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- SUBSHELL --------------------------------
// TODO: The sublect require just priorities not child process
void	execute_subshell(t_ast *root, t_ast *node)
{
	sh.in  = track_dup(STDIN_FILENO);
	sh.out = track_dup(STDOUT_FILENO);
	if (node->child && node->child->type == GRAM_IO_REDIRECT)
		execute_redirection(node->child);
	executor(root, node->child);
	restore_fds(sh.in, sh.out);
}
