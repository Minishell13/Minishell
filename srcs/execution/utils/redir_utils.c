/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:34:47 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/09 23:34:13 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	track_fd(int fd)
{
	if (g_sh.tracked_fds_count < MAX_TRACKED_FDS)
		g_sh.tracked_fds[g_sh.tracked_fds_count++] = fd;
	return (fd);
}

int	track_dup(int oldfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd >= 0)
		return (track_fd(newfd));
	return (-1);
}

void	save_fds(t_fd_backup *backup)
{
	backup->in = track_dup(STDIN_FILENO);
	backup->out = track_dup(STDOUT_FILENO);
}

void	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	generate_tmpfile(t_redir *redir)
{
	char	*temp;

	temp = ft_itoa((unsigned long)(&(redir->limiter)));
	
	if (!temp)
	{
		redir->file = ft_strdup("/tmp/heredoc");
		return ;
	}
	redir->file = ft_strjoin("/tmp/heredoc_", temp);
	free(temp);
}
