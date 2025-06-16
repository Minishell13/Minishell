/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/16 19:15:48 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	change_dir(t_ast *node)
{
	char	*oldpwd;
	char	*path;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = get_env("PWD");
	export_var("OLDPWD", oldpwd, false, true);
	path = node->u_data.args[1];
	if (chdir(path) != 0)
	{
		fdprintf(STDERR_FILENO, CD_ERROR, g_sh.shell, strerror(errno));
		return (EXIT_FAILURE);
	}
	export_var("PWD", getcwd(NULL, 0), false, true);
	return (EXIT_SUCCESS);
}

int	exec_cd(t_ast *node)
{
	int	len;

	len = len_arr(node->u_data.args);
	if (len == 1)
	{
		fdprintf(STDERR_FILENO, NO_PATH, g_sh.shell);
		return (EXIT_FAILURE);
	}
	if (len > 2)
	{
		fdprintf(STDERR_FILENO, TOO_ARGS, g_sh.shell);
		return (EXIT_FAILURE);
	}
	return (change_dir(node));
}
