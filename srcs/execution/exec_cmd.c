/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 19:54:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_helper(t_ast *root, t_ast *cmd)
{
	char	*path;

	reset_signals();
	path = get_path(cmd->data.args[0]);
	execve(path, cmd->data.args, sh.my_env);
	put_error(cmd->data.args[0]);
	get_error(path);
	free(path);
	clear_sh(root);
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
		execve_helper(root, node);
	signals_notif(pid, &status);
}

// //* --------------------------------SIMPLE_COMMAND --------------------------------
// t_error	execute_simple_cmd(t_ast *root, t_ast *node)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	*path;

// 	path = get_path(node->data.args[0]);
// 	if (!path)
// 		return (EXECVE_ERROR);

// 	pid = fork();
// 	if (pid < 0)
// 		return (FORK_ERROR);
// 	if (pid == 0)
// 	{
// 		execve(path, node->data.args);

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
