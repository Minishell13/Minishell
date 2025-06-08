/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 12:50:13 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//* -------------------------------- SUBSHELL --------------------------------
void	execute_subshell(t_ast *node)
{
	t_bool	flag;

	flag = true;
	if (node->child->sibling && node->child->sibling->type == GRAM_IO_REDIRECT)
		flag = execute_redirection(node->child->sibling);
	if (!flag)
		return ;
	run_executor(node->child);
}
