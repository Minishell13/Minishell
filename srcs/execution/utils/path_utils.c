/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:48:57 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 16:04:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_access(char *file, int permission)
{
	if (access(file, permission) == -1)
		return (false);
	return (true);
}

char	*parse_path(char **all_path, char *cmd)
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
	char	*path_var;
	char	**all_path;
	char	*path;

	// 1) If name contains '/', try it directly
	if (ft_strchr(cmd, '/'))
		return ft_strdup(cmd);
	// 2) Get PATH and split
	path_var = getenv("PATH");
	if (!path_var)
		return (ft_strdup(cmd));
	all_path = ft_split(path_var, ':');
	if (!all_path)
		return (ft_strdup(cmd));
	path = parse_path(all_path, cmd);
	return (path);
}
