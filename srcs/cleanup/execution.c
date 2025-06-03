/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:03:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 11:28:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cleanup_loop(char *line)
{
	free(line);
	close_all_tracked_fds();
}

void	clear_sh(t_ast *root)
{
	ast_destroy(root);
	close_all_tracked_fds();
	clear_arr(sh.my_env);
}

void	destroy()
{
	free_all();
	close_all_tracked_fds();
	clear_arr(sh.my_env);
}
