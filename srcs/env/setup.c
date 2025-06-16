/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/16 17:56:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_shell_lvl(void)
{
	char	*lvl_value;
	int		lvl;

	lvl_value = get_env("SHLVL");
	if (!lvl_value)
	{
		export_var("SHLVL", "1", false, false);
		return ;
	}
	lvl = ft_atoi(lvl_value) + 1;
	if (lvl >= 1000)
	{
		fdprintf(STDERR_FILENO, SHLVL_ERROR, lvl);
		lvl = 1;
	}
	free(lvl_value);
	export_var("SHLVL", ft_itoa(lvl), false, true);
}

void	setup_env(char **env)
{
	int	i;

	i = 0;
	g_sh.env = init_arr();
	if (!g_sh.env)
		return ;
	while (env[i])
	{
		g_sh.env = append_arr(g_sh.env, ft_strdup(env[i]));
		i++;
	}
	export_var("PWD", getcwd(NULL, 0), false, true);
	add_shell_lvl();
}
