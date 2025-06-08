/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:57:30 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 21:53:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	default_mode(char *arg, char **v, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) == NONE)
	{
		if (arg[*i] == '$' && arg[*i + 1] == '\0')
			*v = ft_charjoin(*v, arg[*i]);
		else if (arg[*i] == '$' && arg[*i + 1] && is_quote(arg[*i + 1]))
		{
			(*i)++;
			break ;
		}
		else if (try_expand_dollar(arg, v, i))
			continue ;
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

t_bool	expand_var(char *arg, t_qmode mode, t_expand_ctx *ctx)
{
	if (mode == DEFAULT)
	{
		default_mode(arg, &(ctx->v), &(ctx->i));
		append_args(&(ctx->arr), &(ctx->v), true);
		return (true);
	}
	else if (mode == EXPAND)
	{
		(ctx->v) = ft_charjoin(ctx->v, arg[(ctx->i)]);
		((ctx->i))++;
		expand_mode(arg, &(ctx->v), &(ctx->i));
		(ctx->v) = ft_charjoin(ctx->v, arg[(ctx->i)]);
		append_args(&(ctx->arr), &(ctx->v), false);
	}
	else if (mode == LITERAL)
	{
		(ctx->v) = ft_charjoin(ctx->v, arg[(ctx->i)]);
		((ctx->i))++;
		literal_mode(arg, &(ctx->v), &(ctx->i));
		(ctx->v) = ft_charjoin(ctx->v, arg[(ctx->i)]);
		append_args(&(ctx->arr), &(ctx->v), false);
	}
	return (false);
}
