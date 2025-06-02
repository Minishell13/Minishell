/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:48:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 17:16:19 by abnsila          ###   ########.fr       */
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

void	close_all_tracked_fds(void)
{
	int i;

	i = 0;
	while (i < sh.tracked_fds_count)
	{
		close(sh.tracked_fds[i]);
		i++;
	}
	sh.tracked_fds_count = 0;
}

t_bool	check_exit(char **args)
{
	int	len;

	len = len_arr(args);
	if (len_arr(args) == 2 && ft_isnumber(args[1]))
	{
		sh.exit_code = ft_atoi(args[1]);
		return (true);
	}
	if (len > 1)
	{
		if (ft_isnumber(args[1]))
		{
			fdprintf(STDERR_FILENO,
				"minishell: exit: too many arguments\n");
			return (false);
		}
		fdprintf(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n", args[1]);
		sh.exit_code = 2;
		return (true);
	}
	sh.exit_code = EXIT_SUCCESS;
	return (true);
}

int	exec_exit(t_ast *node)
{
	fdprintf(STDERR_FILENO, "exit\n");
	if (check_exit(node->u_data.args))
	{
		destroy();
		exit(sh.exit_code);
	}
	return (EXIT_FAILURE);
}
