/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:05:55 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 13:34:28 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: You foolow rules , they are a diffrent between options and arguments

t_bool	is_builtins(t_ast *node)
{
	char	*cmd;

	cmd = node->u_data.args[0];
	if (ft_strlcmp("cd", cmd))
		return (true);
	else if (ft_strlcmp("echo", cmd))
		return (true);
	else if (ft_strlcmp("env", cmd))
		return (true);
	else if (ft_strlcmp("exit", cmd))
		return (true);
	else if (ft_strlcmp("export", cmd))
		return (true);
	else if (ft_strlcmp("pwd", cmd))
		return (true);
	else if (ft_strlcmp("unset", cmd))
		return (true);
	return (false);
}

int	exec_builtins(t_ast *node)
{
	char	*cmd;

	cmd = node->u_data.args[0];
	if (ft_strlcmp("cd", cmd))
		return (exec_cd(node));
	else if (ft_strlcmp("echo", cmd))
		return (exec_echo(node));
	else if (ft_strlcmp("env", cmd))
		return (exec_env(node));
	else if (ft_strlcmp("exit", cmd))
		return (exec_exit(node));
	else if (ft_strlcmp("export", cmd))
		return (exec_export(node));
	else if (ft_strlcmp("pwd", cmd))
		return (exec_pwd(node));
	else if (ft_strlcmp("unset", cmd))
		return (exec_unset(node));
	return (EXIT_FAILURE);
}
