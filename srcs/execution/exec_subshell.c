/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 07:56:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- SUBSHELL --------------------------------
void	execute_subshell(t_ast *node)
{
	if (node->child->sibling && node->child->sibling->type == GRAM_IO_REDIRECT)
		execute_redirection(node->child->sibling);
	executor(node->child);
}
