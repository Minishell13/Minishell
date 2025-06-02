/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 14:17:48 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
