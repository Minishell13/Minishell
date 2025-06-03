/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_pwd(t_ast *node)
{
	(void)node;
	char *pwd;

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
