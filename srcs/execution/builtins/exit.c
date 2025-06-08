/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:48:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 22:15:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
				"%s: exit: too many arguments\n", g_sh.shell);
			return (false);
		}
		fdprintf(STDERR_FILENO,
			"%s: exit: %s: numeric argument required\n", g_sh.shell, args[1]);
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
