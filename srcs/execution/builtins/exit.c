/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:48:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 18:00:02 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	track_fd(int fd)
{
	if (sh.tracked_fds_count < MAX_TRACKED_FDS)
	{
		sh.tracked_fds[sh.tracked_fds_count++] = fd;
	}
	return fd;
}

int	track_dup(int oldfd)
{
	int newfd = dup(oldfd);
	if (newfd >= 0)
		return track_fd(newfd);
	return -1;
}

int	track_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return -1;
	track_fd(pipefd[0]);
	track_fd(pipefd[1]);
	return 0;
}

void	close_all_tracked_fds(void)
{
	for (int i = 0; i < sh.tracked_fds_count; i++)
		close(sh.tracked_fds[i]);
	sh.tracked_fds_count = 0;
}

int	exec_exit(t_ast *root, t_ast *node)
{
	if (!no_args(node->data.args))
	{
		fdprintf(STDERR_FILENO,
				"minishell: exit: %s : no options allowed\n"
				, node->data.args[1]);	
	}
	//TODO: Cleanup ressources
	restore_fds(sh.in, sh.out);
	close_all_tracked_fds();
	clear_sh(root);
	exit(sh.exit_code);
}
