/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_env(t_ast *node)
{
	int	i;

	if (len_arr(node->u_data.args) > 1)
	{
		fdprintf(STDERR_FILENO,
				"minishell: env: %s: no options or arguments \
allowed\n", node->u_data.args[1]);
		return (EXIT_FAILURE);
	}
	i = 0;
	if (!g_sh.my_env)
	{
		fdprintf(STDERR_FILENO, "minishell: env: no env exist\n");
		return (EXIT_FAILURE);
	}
	while (g_sh.my_env[i])
	{
		if (g_sh.my_env[i])
			ft_putendl_fd(g_sh.my_env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
