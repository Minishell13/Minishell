/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 20:23:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_ast *node)
{
	char *pwd;

	if (!no_args(node->u_data.args))
	{
		builtins_error("pwd", NULL, ": no options allowed");
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd) 
	{
		pwd = get_value("PWD");
		if (!pwd)
		{
			perror("sh");
			return (EXIT_FAILURE);
		}
		printf("%s\n", pwd);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (EXIT_SUCCESS);
}
