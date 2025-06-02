/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:30 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 15:13:41 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_key(char *arg)
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

t_bool	parse_input(char *arg)
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

int	exec_export(t_ast *node)
{
	char	**args;
	args = node->u_data.args;
	args++;
	while (*args)
	{
		if (!ft_strchr(*args, '='))
		{
			if (valid_key(*args) == -1)
			{	
				fdprintf(STDERR_FILENO,
					"minishell: export: %s: not a valid identifier\n", *args);
				return (EXIT_FAILURE);
			}
		}
		else if (parse_input(*args) == false)
		{	
			fdprintf(STDERR_FILENO,
					"minishell: export: %s: not a valid identifier\n", *args);
			return (EXIT_FAILURE);
		}
		args++;
	}
	return (EXIT_SUCCESS);
}
