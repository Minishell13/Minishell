/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:30 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 22:16:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	int	print_export_list(void)
{
	int	i;

	i = 0;
	while (g_sh.env[i])
	{
		if (g_sh.env[i])
			printf("declare -x %s\n", g_sh.env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static	int	valid_key(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (-1);
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && !(ft_isalpha(arg[i]) || arg[i] == '_'))
			return (-1);
		else if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (-1);
		i++;
	}
	return (i);
}

static	t_bool	parse_input(char *arg)
{
	int		end;
	char	*key;
	char	*value;

	end = valid_key(arg);
	if (end != -1)
	{
		key = extract_key(arg, end);
		value = extract_value(arg, end + 1);
		export_var(key, value, true, true);
		return (true);
	}
	return (false);
}

static	int	export_vars(char **args)
{
	int	code;

	code = EXIT_SUCCESS;
	args++;
	while (*args)
	{
		if (!ft_strchr(*args, '='))
		{
			if (valid_key(*args) == -1)
			{
				fdprintf(STDERR_FILENO,
					"%s: export: %s: not a valid identifier\n",
					g_sh.shell, *args);
				code = EXIT_FAILURE;
			}
		}
		else if (parse_input(*args) == false)
		{
			fdprintf(STDERR_FILENO,
				"%s: export: %s: not a valid identifier\n", g_sh.shell, *args);
			code = EXIT_FAILURE;
		}
		args++;
	}
	return (code);
}

int	exec_export(t_ast *node)
{
	char	**args;

	args = node->u_data.args;
	if (!g_sh.env)
		return (EXIT_FAILURE);
	if (len_arr(args) == 1)
		return (print_export_list());
	return (export_vars(args));
}
