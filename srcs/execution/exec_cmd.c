/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 15:25:13 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_fds_except_std(void)
{
	int fd = 3;

	while (fd < MAX_TRACKED_FDS)
	{
		close(fd);
		fd++;
	}
}

void	execve_helper(t_ast *cmd)
{
	char	*path;

	sh.is_child = true;
	close_fds_except_std();
	reset_signals();
	path = get_path(cmd->u_data.args[0]);
	execve(path, cmd->u_data.args, sh.my_env);
	put_error(cmd->u_data.args[0]);
	get_error(path);
	free(path);
	destroy();
	exit(sh.exit_code);
}

void	run_builtins(t_ast *node)
{
	char	*cmd;

	cmd = node->u_data.args[0];
	sh.exit_code = exec_builtins(node);
}

t_bool	run_command(t_ast *node, t_bool no_fork)
{
	pid_t	pid;

	if (no_fork)
		execve_helper(node);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
		execve_helper(node);
	return (pid);
}

void	execute_simple_cmd(t_ast *node, t_bool no_fork)
{
	pid_t	pid;
	int		status;
	t_bool	flag;

	flag = true;
	if (node->child && node->child->type == GRAM_IO_REDIRECT)
		flag = execute_redirection(node->child);
	if (!flag)
		return ;
	expand_cmd_node(node);
	if (!no_fork)
		export_var("_", node->u_data.args[0], false, false);
	if (is_builtins(node))
		return (run_builtins(node));
	pid = run_command(node, no_fork);
	if (pid == -1)
		return ;
	signals_notif(pid, &status);
}

// //* --------------------------------SIMPLE_COMMAND --------------------------------
// t_error	execute_simple_cmd(t_ast *node)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	*path;

// 	path = get_path(node->u_data.args[0]);
// 	if (!path)
// 		return (EXECVE_ERROR);

// 	pid = fork();
// 	if (pid < 0)
// 		return (FORK_ERROR);
// 	if (pid == 0)
// 	{
// 		execve(path, node->u_data.args);

// 		// TODO: Maybe use a custom put error function instead perror
// 		// perror("sh");
// 		put_error(path);
// 		free(path);
// 		ast_destroy(root);
// 		if (errno == ENOENT) exit(NO_FILE_OR_DIR);
// 		if (errno == EACCES) exit(PERMISSION_DENIED);
// 		exit(EXIT_FAILURE);
// 	}
// 	waitpid(pid, &status, 0);
// 	free(path);
// 	return (WEXITSTATUS(status) ? EXECVE_ERROR : SUCCESS);
// }
