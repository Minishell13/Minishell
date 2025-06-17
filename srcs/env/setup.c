/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/17 13:08:59 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	swap_env(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	setup_declare_env(void)
{
	int		i;
	int		j;

	clear_arr(g_sh.declare_env);
	g_sh.declare_env = init_arr();
	if (!g_sh.env || !g_sh.declare_env)
		return ;
	i = 0;
	while (g_sh.env[i])
		g_sh.declare_env = append_arr(g_sh.declare_env,
				ft_strdup(g_sh.env[i++]));
	i = 0;
	while (g_sh.declare_env[i])
	{
		j = i + 1;
		while (g_sh.declare_env[j])
		{
			if (ft_strncmp(g_sh.declare_env[i],
					g_sh.declare_env[j], ft_strlen(g_sh.declare_env[j])) > 0)
				swap_env(&g_sh.declare_env[i], &g_sh.declare_env[j]);
			j++;
		}
		i++;
	}
}

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
	if (!env || !g_sh.env)
		return ;
	while (env[i])
	{
		g_sh.env = append_arr(g_sh.env, ft_strdup(env[i]));
		i++;
	}
	export_var("PWD", getcwd(NULL, 0), false, true);
	add_shell_lvl();
	setup_declare_env();
}
