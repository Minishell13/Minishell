/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:17:40 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/16 17:06:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_exit_code(char *cmd)
{
	if (cmd && ft_strlcmp(cmd, "."))
		g_sh.exit_code = FAILURE;
	else if (errno == ENOENT || (cmd && ft_strlcmp(cmd, "..")))
		g_sh.exit_code = NO_FILE_OR_DIR;
	else if (errno == EACCES)
		g_sh.exit_code = PERMISSION_DENIED;
	else
		g_sh.exit_code = ERROR;
}

static void	format_error(char *format, char *arg, char *error)
{
	char	buffer[1024];

	ft_bzero(buffer, sizeof(buffer));
	if (!format || !error)
		return ;
	ft_strlcat(buffer, g_sh.shell, sizeof(buffer));
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

void	ft_perror(char *cmd)
{
	int	i;

	i = -1;
	while (g_sh.env[++i])
	{
		if (ft_strncmp(g_sh.env[i], "PATH=", 5) == 0)
			break ;
	}
	if (!g_sh.env[i])
		format_error("%s: %s: %s", cmd, NO_FILE_DIR);
	else if (!cmd)
		format_error("%s: %s: %s", " ", CMD_NOT_FOUND);
	else if (ft_strlcmp(cmd, "/"))
		format_error("%s: %s: %s", cmd, IS_DIR);
	else if (ft_strchr(cmd, '/'))
		format_error("%s: %s: %s", cmd, strerror(errno));
	else
		format_error("%s: %s: %s", cmd, CMD_NOT_FOUND);
	set_exit_code(cmd);
}
