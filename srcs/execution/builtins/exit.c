/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:48:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/17 11:43:30 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	t_bool	check_exit(char **args, int len)
{
	t_bool	overflow;
	long	value;

	if (len == 2 && ft_isnumber(args[1]))
	{
		value = ft_strtol(args[1], &overflow);
		if (overflow)
		{
			fdprintf(STDERR_FILENO, EXIT_ERROR, g_sh.shell, args[1]);
			g_sh.exit_code = FAILURE;
		}
		else
			g_sh.exit_code = (unsigned char)value;
	}
	else if (len > 1)
	{
		if (ft_isnumber(args[1]))
		{
			fdprintf(STDERR_FILENO, TOO_ARGS, g_sh.shell);
			return (false);
		}
		fdprintf(STDERR_FILENO, EXIT_ERROR, g_sh.shell, args[1]);
		g_sh.exit_code = FAILURE;
	}
	return (true);
}

int	exec_exit(t_ast *node)
{
	int	len;

	len = len_arr(node->u_data.args);
	fdprintf(STDERR_FILENO, "exit\n");
	if (check_exit(node->u_data.args, len))
	{
		destroy();
		exit(g_sh.exit_code);
	}
	return (EXIT_FAILURE);
}
