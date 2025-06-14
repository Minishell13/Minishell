/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/10 19:56:33 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = get_env("PWD");
		if (!pwd)
		{
			fdprintf(STDERR_FILENO, PWD_ERROR, g_sh.shell, strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
