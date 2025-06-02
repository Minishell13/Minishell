/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 07:53:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO The heredoc must be restored or somting if it is attached with &&, ||
//* -------------------------------- AND_OR --------------------------------
void	execute_and_or(t_ast *node)
{
	executor(node->child);
	if (node->type == GRAM_OPERATOR_AND && sh.exit_code == 0)
		executor(node->child->sibling);
	else if (node->type == GRAM_OPERATOR_OR && sh.exit_code != 0)
		executor(node->child->sibling);
}
