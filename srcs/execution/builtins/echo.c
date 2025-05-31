/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:46:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 07:20:39 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(t_ast *node)
{
	int		i;
	char	**args;
	t_bool	flag;

	if (write(STDOUT_FILENO, "", 0) == -1)
		return (EXIT_FAILURE);
	i = 1;
	flag = false;
	args = node->data.args;
	while (args[i] && check_echo(args[i]))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
