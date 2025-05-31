/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 16:06:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_ast *node)
{
	int	i;

	if (!no_args(node->data.args))
	{
		fdprintf(STDERR_FILENO,
				"minishell: env: no options allowed\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	if (!sh.my_env)
		return (EXIT_FAILURE);
	while (sh.my_env[i])
	{
		if (!sh.my_env[i])
		{
			i++;
			continue ;
		}
		ft_putendl_fd(sh.my_env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
