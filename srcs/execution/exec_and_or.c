/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 13:31:51 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//* -------------------------------- AND_OR --------------------------------
void	execute_and_or(t_ast *node)
{
	run_executor(node->child);
	if (node->type == GRAM_OPERATOR_AND && g_sh.exit_code == 0)
		run_executor(node->child->sibling);
	else if (node->type == GRAM_OPERATOR_OR && g_sh.exit_code != 0)
		run_executor(node->child->sibling);
}
