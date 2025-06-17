/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:17:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/17 12:50:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*extract_key(char *arg, int end)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strdup("");
	while (arg[i] && i < end)
	{
		key = ft_charjoin(key, arg[i]);
		i++;
	}
	return (key);
}

char	*extract_value(char *arg, int end)
{
	char	*value;

	value = ft_strdup("");
	while (arg[end])
	{
		value = ft_charjoin(value, arg[end]);
		end++;
	}
	return (value);
}

void	export_var(char *k, char *v, t_bool alcd1, t_bool alcd2)
{
	char	*key;
	char	*val;

	if (!k || !v)
		return ;
	if (alcd1)
		key = k;
	else
		key = ft_strdup(k);
	if (alcd2)
		val = v;
	else
		val = ft_strdup(v);
	add_var(key, val);
	free(key);
	free(val);
	setup_declare_env();
}

void	unset_var(char *key)
{
	int		i;
	size_t	key_len;
	char	**new_env;

	i = 0;
	new_env = init_arr();
	key_len = ft_strlen(key);
	while (g_sh.env[i])
	{
		if (ft_strncmp(g_sh.env[i], key, key_len) == 0
			&& g_sh.env[i][key_len] && g_sh.env[i][key_len] == '=')
		{
			i++;
			continue ;
		}
		new_env = append_arr(new_env, ft_strdup(g_sh.env[i]));
		i++;
	}
	clear_arr(g_sh.env);
	g_sh.env = new_env;
	setup_declare_env();
}
