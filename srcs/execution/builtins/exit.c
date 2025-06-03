/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:48:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	track_fd(int fd)
{
	if (g_sh.tracked_fds_count < MAX_TRACKED_FDS)
		g_sh.tracked_fds[g_sh.tracked_fds_count++] = fd;
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
	while (i < g_sh.tracked_fds_count)
	{
		close(g_sh.tracked_fds[i]);
		i++;
	}
	g_sh.tracked_fds_count = 0;
}

static	t_bool	check_exit(char **args)
{
	int	len;

	len = len_arr(args);
	if (len_arr(args) == 2 && ft_isnumber(args[1]))
	{
		g_sh.exit_code = ft_atoi(args[1]);
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
		g_sh.exit_code = 2;
		return (true);
	}
	return (true);
}

int	exec_exit(t_ast *node)
{
	fdprintf(STDERR_FILENO, "exit\n");
	if (check_exit(node->u_data.args))
	{
		destroy();
		exit(g_sh.exit_code);
	}
	return (EXIT_FAILURE);
}
