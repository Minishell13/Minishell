/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:18 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 19:26:37 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- PIPELINE --------------------------------


// void run_one_stage(t_ast *root, t_ast *node)
// {
// 	if (!node)
// 	{
// 		clear_sh(root);
// 		exit(EXIT_FAILURE);
// 	}
// 	switch (node->type)
// 	{
// 		case GRAM_SIMPLE_COMMAND:
// 			execute_simple_cmd(root, node, true);
// 			break;

// 		case GRAM_SUBSHELL:
// 			execute_subshell(root, node);
// 			clear_sh(root);
// 			exit(sh.exit_code);
// 			break;

// 		default:
// 			ft_putstr_fd("minishell: invalid pipeline stage\n", STDERR_FILENO);
// 			clear_sh(root);
// 			exit(EXIT_FAILURE);
// 	}
// }

// void	exec_left(t_ast *root, t_ast *left)
// {
// 	sh.pids[0] = fork();
// 	if (sh.pids[0] < 0)
// 		return ;
// 	if (sh.pids[0] == 0)
// 	{
// 		redirect_fds(root, STDOUT_FILENO);
// 		if (left->type == GRAM_PIPE)
// 			execute_pipeline(root, left);
// 		else
// 			run_one_stage(root, left);
// 	}
// }

// void	exec_right(t_ast *root, t_ast *right)
// {
// 	sh.pids[1] = fork();
// 	if (sh.pids[1] < 0)
// 		return ;
// 	if (sh.pids[1] == 0)
// 	{
// 		redirect_fds(root, STDIN_FILENO);
// 		if (right->type == GRAM_PIPE)
// 			execute_pipeline(root, right);
// 		else
// 			run_one_stage(root, right);
// 	}
// }

// void	execute_pipeline(t_ast *root, t_ast *node)
// {
// 	int	status;

// 	if (!node->child || !node->child->sibling)
// 		return ;

// 	if (pipe(sh.pipefd) < 0)
// 		return ;

// 	exec_left(root, node->child);
// 	exec_right(root, node->child->sibling);

// 	// 3) PARENT: clean up and wait
// 	close(sh.pipefd[0]);
// 	close(sh.pipefd[1]);
// 	signals_notif(sh.pids[0], &status);
// 	signals_notif(sh.pids[1], &status);

// 	// return the exit status of the rightmost stage
// 	sh.exit_code = WEXITSTATUS(status);
// }




void run_one_stage(t_ast *root, t_ast *node)
{
	if (!node)
	{
		clear_sh(root);
		exit(EXIT_FAILURE);
	}
	switch (node->type)
	{
		case GRAM_SIMPLE_COMMAND:
			execute_simple_cmd(root, node, true);
			break;

		case GRAM_SUBSHELL:
			execute_subshell(root, node);
			clear_sh(root);
			exit(sh.exit_code);
			break;

		case GRAM_PIPE:
			execute_pipeline(root, node);
			clear_sh(root);
			exit(sh.exit_code);
			break;

		default:
			fdprintf(STDERR_FILENO, "minishell: invalid pipeline stage\n");
			clear_sh(root);
			exit(EXIT_FAILURE);
	}
}

#define MAX_PIPE 1024

static void setup_pipe(int i, t_bool has_next)
{
	if (has_next)
		pipe(sh.pipefd[i % 2]);
}

static void redirect_pipes(int i, t_bool has_next)
{
	if (i > 0)
		dup2(sh.pipefd[(i + 1) % 2][0], STDIN_FILENO);
	if (has_next)
		dup2(sh.pipefd[i % 2][1], STDOUT_FILENO);
}

static void close_pipes_in_child(int i, t_bool has_next)
{
	if (i > 0)
	{
		close(sh.pipefd[(i + 1) % 2][0]);
		close(sh.pipefd[(i + 1) % 2][1]);
	}
	if (has_next)
	{
		close(sh.pipefd[i % 2][0]);
		close(sh.pipefd[i % 2][1]);
	}
}

static void close_pipes_in_parent(int i)
{
	if (i > 0)
	{
		close(sh.pipefd[(i + 1) % 2][0]);
		close(sh.pipefd[(i + 1) % 2][1]);
	}
}

void execute_pipeline(t_ast *root, t_ast *pipeline)
{
	t_ast *cmd;
	int i = 0;
	int status;
	pid_t pids[MAX_PIPE];
	t_bool has_next;

	cmd = pipeline->child;
	while (cmd)
	{
		has_next = cmd->sibling != NULL;
		setup_pipe(i, has_next);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			redirect_pipes(i, has_next);
			close_pipes_in_child(i, has_next);
			run_one_stage(root, cmd);
			exit(EXIT_FAILURE); // only reached if exec fails
		}
		close_pipes_in_parent(i);
		cmd = cmd->sibling;
		i++;
	}
	while (i--)
		waitpid(pids[i], &status, 0);
	sh.exit_code = WEXITSTATUS(status);
}



