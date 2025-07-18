/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/10 19:51:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_env(t_ast *node)
{
	int	i;

	if (len_arr(node->u_data.args) > 1)
	{
		fdprintf(STDERR_FILENO, NO_OP_ARGS, g_sh.shell, node->u_data.args[1]);
		return (EXIT_FAILURE);
	}
	i = 0;
	if (!g_sh.env)
	{
		fdprintf(STDERR_FILENO, NO_ENV, g_sh.shell);
		return (EXIT_FAILURE);
	}
	while (g_sh.env[i])
	{
		if (g_sh.env[i])
			ft_putendl_fd(g_sh.env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
