/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:46:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	t_bool	check_echo(char *arg)
{
	size_t  len;

	if (!arg)
		return (false);
	len = ft_strlen(arg);
	if (*arg != '-' || (len == 1 && *arg == '-'))
		return (false);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (false);
		arg++;
	}
	return (true);
}

int	exec_echo(t_ast *node)
{
	int		i;
	char	**args;
	t_bool	flag;

	if (write(STDOUT_FILENO, "", 0) == -1)
		return (EXIT_FAILURE);
	i = 1;
	flag = false;
	args = node->u_data.args;
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
