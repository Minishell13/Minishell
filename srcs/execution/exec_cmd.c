/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/16 18:46:41 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_fds_except_std(void)
{
	int	fd;

	fd = 3;
	while (fd < MAX_TRACKED_FDS)
	{
		close(fd);
		fd++;
	}
}

static void	execve_helper(t_ast *cmd)
{
	char	*path;

	close_fds_except_std();
	reset_signals();
	path = get_path(cmd->u_data.args[0]);
	execve(path, cmd->u_data.args, g_sh.env);
	ft_perror(cmd->u_data.args[0]);
	free(path);
	destroy();
	exit(g_sh.exit_code);
}

static void	run_builtins(t_ast *node)
{
	t_fd_backup	backup;
	t_bool		flag;

	flag = true;
	save_fds(&backup);
	if (node->child && node->child->type == GRAM_IO_REDIRECT)
		flag = execute_redirection(node->child);
	if (!flag)
		return ;
	g_sh.exit_code = exec_builtins(node);
	restore_fds(backup.in, backup.out);
}

static int	run_command(t_ast *node)
{
	pid_t	pid;
	t_bool	flag;

	flag = true;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		g_sh.interactive = false;
		if (node->child && node->child->type == GRAM_IO_REDIRECT)
			flag = execute_redirection(node->child);
		if (!flag)
			return (-1);
		execve_helper(node);
	}
	return (pid);
}

void	execute_simple_cmd(t_ast *node, t_bool no_fork)
{
	pid_t	pid;
	int		status;
	t_bool	flag;

	expand_cmd_node(node);
	if (is_builtins(node))
		return (run_builtins(node));
	flag = true;
	if (no_fork)
	{
		if (node->child && node->child->type == GRAM_IO_REDIRECT)
			flag = execute_redirection(node->child);
		if (!flag)
			return ;
		execve_helper(node);
	}
	pid = run_command(node);
	if (pid == -1)
		return ;
	signals_notif(pid, &status);
}
