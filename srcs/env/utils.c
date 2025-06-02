/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:12:28 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 16:22:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	var_exist(char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (sh.my_env[i])
	{
		if (ft_strncmp(sh.my_env[i], key, key_len) == 0
			&& sh.my_env[i][key_len] && sh.my_env[i][key_len] == '=')
		{
			return (true);
		}
		i++;
	}
	return (false);
}

int	get_var_index(char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (sh.my_env[i])
	{
		if (ft_strncmp(sh.my_env[i], key, key_len) == 0
			&& sh.my_env[i][key_len] && sh.my_env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_value(char *key)
{
	int		i;
	size_t	key_len;
	char	*value;

	i = 0;
	key_len = ft_strlen(key);
	while (sh.my_env[i])
	{
		if (ft_strncmp(sh.my_env[i], key, key_len) == 0
			&& sh.my_env[i][key_len] && sh.my_env[i][key_len] == '=')
		{
			value = sh.my_env[i] + key_len;
			value = ft_strdup(value + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	add_var(char *key, char *value)
{
	char	*tmp;
	char	*new_var;
	int		var_index;

	var_index = get_var_index(key);
	tmp = ft_strjoin(key, "=");
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	if (var_index != -1)
	{
		free(sh.my_env[var_index]);
		sh.my_env[var_index] = new_var;
	}
	else
		sh.my_env = append_arr(sh.my_env, new_var);
}
