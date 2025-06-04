/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:03:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/04 15:25:56 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
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

void	cleanup_loop(char *line)
{
	free(line);
	close_all_tracked_fds();
}

void	destroy()
{
	free_all();
	close_all_tracked_fds();
	clear_arr(g_sh.env);
}
