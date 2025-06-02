/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:57:30 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 12:54:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
void	default_mode(char *arg, char **v, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) == NONE)
	{
		// Keep the ($) at the end
		if (arg[*i] == '$' && arg[*i + 1] == '\0')
			*v = ft_charjoin(*v, arg[*i]);
		// Skip the ($) if quote comes after
		else if (arg[*i] == '$' && arg[*i + 1] && is_quote(arg[*i + 1]))
		{
			(*i)++;
			break ;
		}
		else if (try_expand_dollar(arg, v, i))
			continue ;
		// Do not expand simple char
		else
			*v = ft_charjoin(*v, arg[*i]);
		(*i)++;
	}
}

void	expand_mode(char *arg, char **v, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) != DOUBLE_Q)
	{
		if (try_expand_dollar(arg, v, i))
			continue ;
		// Do not expand simple char
		else
			*v = ft_charjoin(*v, arg[*i]);
		(*i)++;
	}
}

void	literal_mode(char *arg, char **v, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) != SINGLE_Q)
	{
		*v = ft_charjoin(*v, arg[*i]);
		(*i)++;
	}
}

void	append_args(char ***arr, char **v, t_bool split)
{
	if (split)
	{
		*arr = inner_merge_arr(*arr, ft_split(*v, ' '));
		free(*v);
	}
	else
	{
		if (len_arr(*arr) == 0)
		{	
			*arr = append_arr(*arr, ft_strdup(*v));
			free(*v);
		}
		else
			*last_item_ptr(*arr) = ft_conststrjoin(*last_item_ptr(*arr), *v);
	}
}

//TODO: If you gonna use wildcard logic unsure you include quotes also
t_bool	process_mode(char *arg, t_qmode mode, char ***arr, char **v, int *i)
{
		if (mode == DEFAULT)
		{
			// printf("-------------- Default ---------------\n");
			default_mode(arg, v, i);
			append_args(arr, v, true);
			return (true);
		}
		else if (mode == EXPAND)
		{
			// *v = ft_charjoin(*v, arg[*i]);
			(*i)++;
			// printf("-------------- Expand ---------------\n");
			expand_mode(arg, v, i);
			// *v = ft_charjoin(*v, arg[*i]);
			append_args(arr, v, false);
		}
		else if (mode == LITERAL)
		{
			// *v = ft_charjoin(*v, arg[*i]);
			(*i)++;
			// printf("-------------- Literal ---------------\n");
			literal_mode(arg, v, i);
			// *v = ft_charjoin(*v, arg[*i]);
			append_args(arr, v, false);
		}
		return (false);
}
