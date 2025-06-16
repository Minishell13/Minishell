/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:34:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/16 21:26:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell	g_sh;

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (ac != 1)
	{
		fd_putstr_fd(SHELL_ERROR, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	launch_shell(env);
	return (g_sh.exit_code);
}
