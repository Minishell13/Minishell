/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 16:36:55 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_pwd(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 1 && *arg == '-')
		return (true);
	else if (len > 1 && *arg == '-')
		return (false);
	return (true);
}

int	exec_pwd(t_ast *node)
{
	char *pwd;

	if (!no_args(node->u_data.args) && !check_pwd(node->u_data.args[1]))
	{
		fdprintf(STDERR_FILENO,
				"minishell: pwd: %s: no options allowed\n", node->u_data.args[1]);
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd) 
	{
		pwd = get_value("PWD");
		if (!pwd)
		{
			fdprintf(STDERR_FILENO,
				"minishell: pwd: %s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
