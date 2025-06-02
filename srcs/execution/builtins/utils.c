/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:16:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 15:01:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_echo(char *arg)
{
	size_t  len;

	if (!arg)
		return (false);
	len = ft_strlen(arg);
	if (len == 2 && (arg[0] == '-' && arg[1] == 'n'))
		return (true);
	return (false);
}

t_bool	no_options(char *arg)
{
	if (!arg)
		return (false);
	if (arg && arg[0] == '-')
		return (false);
	return (true);
}

t_bool	no_args(char **args)
{
	int	len;

	if (!args)
		return (false);
	len = len_arr(args);
	if (len > 1)
		return (false);
	return (true);
}

int	builtins_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}
