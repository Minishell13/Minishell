/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:33:52 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/10 19:38:25 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parent_cleanup(pid_t pids[MAX_PIPE], int i, int *status)
{
	int	j;

	j = 0;
	while (j < i)
		signals_notif(pids[j++], status);
}

static void	child_exec(t_ast *stage, int i, t_bool has_next)
{
	g_sh.interactive = false;
	redirect_pipes(i, has_next);
	close_pipes_in_child(i, has_next);
	if (stage->type == GRAM_SIMPLE_COMMAND)
		execute_simple_cmd(stage, true);
	else
		run_executor(stage);
	destroy();
	exit(g_sh.exit_code);
}

static void	pipeline_loop(t_ast **stages, int total, pid_t *pids)
{
	int		i;
	t_bool	has_next;

	i = 0;
	while (i < total)
	{
		has_next = 0;
		if (i < total - 1)
			has_next = true;
		setup_pipe(i, has_next);
		pids[i] = fork();
		if (pids[i] < 0)
		{
			fdprintf(STDERR_FILENO, "fork error\n");
			destroy();
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
			child_exec(stages[i], i, has_next);
		close_pipes_in_parent(i);
		i++;
	}
}

void	execute_pipeline(t_ast *pipeline)
{
	t_ast	*stages[MAX_PIPE];
	pid_t	pids[MAX_PIPE];
	int		total;
	int		status;

	total = 0;
	signal(SIGINT, SIG_IGN);
	collect_pipeline_stages(pipeline, stages, &total);
	pipeline_loop(stages, total, pids);
	parent_cleanup(pids, total, &status);
	g_sh.exit_code = WEXITSTATUS(status);
}
