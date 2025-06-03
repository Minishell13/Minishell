/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:34:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 21:34:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell	g_sh;

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	launch_shell(ev);
	return (g_sh.exit_code);
}
