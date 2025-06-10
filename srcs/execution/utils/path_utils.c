/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:48:57 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/09 00:42:23 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	check_access(char *file, int permission)
{
	if (access(file, permission) == -1)
		return (false);
	return (true);
}

static char	*parse_path(char **all_path, char *cmd)
{
	int		i;
	char	*temp;
	char	*path;
	char	*result;

	i = 0;
	result = NULL;
	while (all_path[i] && !result)
	{
		temp = ft_strjoin("/", cmd);
		if (!temp)
			break ;
		path = ft_strjoin(all_path[i], temp);
		free(temp);
		if (path && check_access(path, X_OK))
			result = path;
		else
			free(path);
		i++;
	}
	ft_free_array(all_path);
	if (!result)
		result = ft_strdup(cmd);
	return (result);
}

char	*get_path(char *cmd)
{
	int		i;
	char	**all_path;
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	i = -1;
	while (g_sh.env[++i])
	{
		if (ft_strncmp(g_sh.env[i], "PATH=", 5) == 0)
			break ;
	}
	if (!g_sh.env[i])
		return (ft_strdup(cmd));
	all_path = ft_split(g_sh.env[i] + 5, ':');
	if (!all_path)
		return (ft_strdup(cmd));
	path = parse_path(all_path, cmd);
	return (path);
}
