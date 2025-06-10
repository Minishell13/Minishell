/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:57:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/10 17:01:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setup_pipe(int i, t_bool has_next)
{
	if (has_next)
	{
		if (pipe(g_sh.pipefd[i % 2]) != 0)
		{
			fdprintf(STDERR_FILENO, "pipe error\n");
			destroy();
			exit(EXIT_FAILURE);
		}
	}
}

void	redirect_pipes(int i, t_bool has_next)
{
	if (i > 0)
		dup2(g_sh.pipefd[(i + 1) % 2][READ], STDIN_FILENO);
	if (has_next)
		dup2(g_sh.pipefd[i % 2][WRITE], STDOUT_FILENO);
}

void	close_pipes_in_child(int i, t_bool has_next)
{
	if (i > 0)
	{
		close(g_sh.pipefd[(i + 1) % 2][READ]);
		close(g_sh.pipefd[(i + 1) % 2][WRITE]);
	}
	if (has_next)
	{
		close(g_sh.pipefd[i % 2][READ]);
		close(g_sh.pipefd[i % 2][WRITE]);
	}
}

void	close_pipes_in_parent(int i)
{
	if (i > 0)
	{
		close(g_sh.pipefd[(i + 1) % 2][READ]);
		close(g_sh.pipefd[(i + 1) % 2][WRITE]);
	}
}

void	collect_pipeline_stages(t_ast *node, t_ast **stages, int *count)
{
	if (!node)
		return ;
	if (node->type == GRAM_PIPE)
	{
		collect_pipeline_stages(node->child, stages, count);
		collect_pipeline_stages(node->child->sibling, stages, count);
	}
	else
	{
		stages[*count] = node;
		(*count)++;
	}
}
