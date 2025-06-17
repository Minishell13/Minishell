/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:58:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/17 17:13:48 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_quote	is_quote(char c)
{
	if (c == '\'')
		return (SINGLE_Q);
	else if (c == '"')
		return (DOUBLE_Q);
	else
		return (NONE);
}

static char	*get_exit_code(void)
{
	char	*value;

	value = ft_itoa(g_sh.exit_code);
	if (!value)
		return (ft_strdup("1"));
	return (value);
}

static int	is_valid(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*extract_var_value(char *arg, int *i)
{
	char	*key;
	char	*value;

	key = ft_strdup("");
	while (arg[*i] && (is_quote(arg[*i]) == NONE)
		&& is_valid(arg[*i]) && ft_isspace(arg[*i]) == 0)
	{
		key = ft_charjoin(key, arg[*i]);
		if (!key)
			return (NULL);
		(*i)++;
	}
	value = get_env(key);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

t_bool	try_expand_dollar(char *arg, char **value, int *i)
{
	if (arg[*i] != '$')
		return (false);
	else if (arg[*i + 1] && is_quote(arg[*i + 1]))
		return (false);
	else if (arg[*i + 1] == '?')
	{
		*value = ft_conststrjoin(*value, get_exit_code());
		*i += 2;
	}
	else if (arg[*i + 1] && ft_isalnum(arg[*i + 1]) == 0
		&& arg[*i + 1] != '_' && is_quote(arg[*i + 1]) == NONE)
	{
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
	else
	{
		(*i)++;
		*value = ft_conststrjoin(*value, extract_var_value(arg, i));
	}
	return (true);
}
