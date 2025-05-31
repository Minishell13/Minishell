/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:34:47 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 17:05:45 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

// void	redirect_fds(t_ast *root, int fd)
// {
// 	if (fd == STDOUT_FILENO)
// 	{	
// 		close(sh.pipefd[0]);
// 		if (dup2(sh.pipefd[1], STDOUT_FILENO) == -1)
// 		{
// 			clear_sh(root);
// 			close(sh.pipefd[1]);
// 			exit(EXIT_FAILURE);
// 		}
// 		close(sh.pipefd[1]);
// 	}
// 	else if (fd == STDIN_FILENO)
// 	{	
// 		close(sh.pipefd[1]);
// 		if (dup2(sh.pipefd[0], STDIN_FILENO) == -1)
// 		{
// 			clear_sh(root);
// 			close(sh.pipefd[0]);
// 			exit(EXIT_FAILURE);
// 		}
// 		close(sh.pipefd[0]);
// 	}
// }

void	generate_tmpfile(t_redir *redir)
{
	char	*temp;

	temp = ft_itoa(getpid());
	if (!temp)
	{
		redir->file = ft_strdup("/tmp/heredoc");
		return ;
	}
	redir->file = ft_strjoin("/tmp/heredoc_", temp);
	free(temp);
}
