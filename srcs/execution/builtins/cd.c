/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/10 19:49:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_cd(t_ast *node)
{
	char	*path;
	int		len;

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
	path = node->u_data.args[1];
	export_var("OLDPWD", getcwd(NULL, 0), false, true);
	if (chdir(path) != 0)
	{
		fdprintf(STDERR_FILENO, CD_ERROR, g_sh.shell, strerror(errno));
		return (EXIT_FAILURE);
	}
	export_var("PWD", getcwd(NULL, 0), false, true);
	return (EXIT_SUCCESS);
}
