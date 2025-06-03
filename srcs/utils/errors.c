/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:17:40 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 10:51:55 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_code(char *path)
{
	if (path && (ft_strlcmp(path, ".") || ft_strlcmp(path, "..")))
		sh.exit_code = 2;
	else if (errno == ENOENT)
		sh.exit_code = NO_FILE_OR_DIR;
	else if (errno == EACCES)
		sh.exit_code = PERMISSION_DENIED;
	else
		sh.exit_code = ERROR;
}

void	format_error(char *format, char *arg, char *error)
{
	char	buffer[1024];

	ft_bzero(buffer, sizeof(buffer));
	if (!format || !error)
		return ;
	ft_strlcat(buffer, "minishell", sizeof(buffer));
	ft_strlcat(buffer, ": ", sizeof(buffer));
	if (arg)
	{
		ft_strlcat(buffer, arg, sizeof(buffer));
		ft_strlcat(buffer, ": ", sizeof(buffer));
	}
	ft_strlcat(buffer, error, sizeof(buffer));
	ft_strlcat(buffer, "\n", sizeof(buffer));
	write(STDERR_FILENO, buffer, ft_strlen(buffer));
}

void	put_error(char *cmd, char *path)
{
	int	i;

	i = -1;
	while (sh.my_env[++i])
	{
		if (ft_strncmp(sh.my_env[i], "PATH=", 5) == 0)
			break ;
	}
	if (!sh.my_env[i])
		format_error("%s: %s: %s", cmd, "No such file or directory");
	else if (!cmd)
		format_error("%s: %s: %s", " ", "command not found");
	else if (ft_strlcmp(cmd, "/"))
		format_error("%s: %s: %s", cmd, "Is a directory");
	else if (ft_strchr(cmd, '/'))
		format_error("%s: %s: %s", cmd, strerror(errno));
	else
		format_error("%s: %s: %s", cmd, "command not found");
	set_exit_code(path);
}
