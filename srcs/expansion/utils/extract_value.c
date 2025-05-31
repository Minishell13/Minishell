/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:58:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/22 11:08:45 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_minishell	sh;

char	*get_exit_code()
{
	char	*value;

	value = ft_itoa(sh.exit_code);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

int	is_valid(char c)
{
	return (ft_isalnum(c) || c == '_');
}

t_quote	is_quote(char c)
{
	if (c == '\'')
		return (SINGLE_Q);
	else if (c == '"')
		return (DOUBLE_Q);
	else
		return (NONE);
}

char	*extract_var_value(char *arg, int *i)
{
	char	*var;
	char	*value;

	var = ft_strdup("");
	while (arg[*i] && (is_quote(arg[*i]) == NONE)
		&& is_valid(arg[*i]) && ft_isspace(arg[*i]) == 0)
	{
		var = ft_charjoin(var, arg[*i]);
		if (!var)
			return (NULL);
		(*i)++;
	}
	value = getenv(var);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

t_bool	try_expand_dollar(char *arg, char **value, int *i)
{
	if (arg[*i] != '$')
		return (false);
	// Do not expand ($' and $")
	else if (arg[*i + 1] && is_quote(arg[*i + 1]))
		return (false);
	// Expand to exit code
	else if (arg[*i + 1] == '?')
	{	
		*value = ft_conststrjoin(*value, get_exit_code());
		*i += 2;
	}
	// Do not expand special char exept for ($?) ($_...)
	else if (arg[*i + 1] && ft_isalnum(arg[*i + 1]) == 0
		&& arg[*i + 1] != '_' && is_quote(arg[*i + 1]) == NONE)
	{
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
	// Expand var to *value
	else
	{
		(*i)++;
		*value = ft_conststrjoin(*value, extract_var_value(arg, i));
	}
	return (true);
}
