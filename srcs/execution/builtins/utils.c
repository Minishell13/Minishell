/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:16:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 07:15:30 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_echo(char *arg)
{
	size_t  len;
	len = ft_strlen(arg);
	if (len == 2 && (arg[0] == '-' && arg[1] == 'n'))
		return (true);
	return (false);
}

t_bool	no_options(char *arg)
{
	if (arg && arg[0] == '-')
		return (false);
	return (true);
}

t_bool	no_args(char **args)
{
	int	len;

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
