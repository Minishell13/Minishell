/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/01 15:51:41 by abnsila          ###   ########.fr       */
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

void	execve_helper(t_ast *root, t_ast *cmd)
{
	(void)root;
	char	*path;

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

void	execute_simple_cmd(t_ast *root, t_ast *node, t_bool no_fork)
{
	pid_t	pid;
	int		status;

	if (node->child && node->child->type == GRAM_IO_REDIRECT)
		execute_redirection(node->child);
	// Execute Builtins
	if (is_builtins(node))
	{
		sh.exit_code = exec_builtins(root, node);
		return ;
	}
	// Execute Simple Command
	expand_cmd_node(node, process_mode_1);
	if (no_fork)
		execve_helper(root, node);
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		fdprintf(STDERR_FILENO, "FORK()\n");	
		execve_helper(root, node);
	}
	signals_notif(pid, &status);
}

// //* --------------------------------SIMPLE_COMMAND --------------------------------
// t_error	execute_simple_cmd(t_ast *root, t_ast *node)
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
