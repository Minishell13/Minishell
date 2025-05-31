/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 16:04:29 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_var(char *k, char *v, t_bool alcd1, t_bool alcd2)
{
	char	*key;
	char	*val;

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
}

void	add_shell_lvl()
{
	char	*lvl_value;
	int		lvl;

	lvl_value = get_value("SHLVL");
	if (!lvl_value)
	{
		export_var("SHLVL", "1", false, false);
		return ;
	}
	lvl = ft_atoi(lvl_value) + 1;
	printf("lvl: %d\n", lvl - 1);
	if (lvl >= 1000)
	{
		fdprintf(STDERR_FILENO,
				"warning: shell level (%d) too high, resetting to 1\n", lvl);
		lvl = 1;
	}
	free(lvl_value);
	export_var("SHLVL", ft_itoa(lvl), false, true);
}

void	setup_env(char **env)
{
	int	i;

	i = 0;
	sh.my_env = init_arr();
	if (!sh.my_env)
		return ;
	while (env[i])
	{
		sh.my_env = append_arr(sh.my_env, ft_strdup(env[i]));
		i++;
	}
	add_shell_lvl();
}
