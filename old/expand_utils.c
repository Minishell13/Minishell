/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:11:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 18:05:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	expand_var(char *arg, t_qmode mode, char ***arr, char **v, int *i)
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
			*v = ft_charjoin(*v, arg[*i]);
			(*i)++;
			// printf("-------------- Expand ---------------\n");
			expand_mode(arg, v, i);
			*v = ft_charjoin(*v, arg[*i]);
			append_args(arr, v, false);
		}
		else if (mode == LITERAL)
		{
			*v = ft_charjoin(*v, arg[*i]);
			(*i)++;
			// printf("-------------- Literal ---------------\n");
			literal_mode(arg, v, i);
			*v = ft_charjoin(*v, arg[*i]);
			append_args(arr, v, false);
		}
		return (false);
}

t_bool	expand_var(char *arg, t_qmode mode, t_expand_ctx *ctx)
{
	if (mode == DEFAULT)
	{
		default_mode(arg, ctx->v, ctx->i);
		append_args(ctx->arr, ctx->v, true);
		return (true);
	}
	else if (mode == EXPAND)
	{
		*(ctx->v) = ft_charjoin(*(ctx->v), arg[*(ctx->i)]);
		(*(ctx->i))++;
		expand_mode(arg, ctx->v, ctx->i);
		*(ctx->v) = ft_charjoin(*(ctx->v), arg[*(ctx->i)]);
		append_args(ctx->arr, ctx->v, false);
	}
	else if (mode == LITERAL)
	{
		*(ctx->v) = ft_charjoin(*(ctx->v), arg[*(ctx->i)]);
		(*(ctx->i))++;
		literal_mode(arg, ctx->v, ctx->i);
		*(ctx->v) = ft_charjoin(*(ctx->v), arg[*(ctx->i)]);
		append_args(ctx->arr, ctx->v, false);
	}
	return (false);
}

char	**expand_wildcard(char **in_arr)
{
	char	**arr;
	char	**matches;
	int		i;
	t_qp	*qp;

	arr = init_arr();
	i = 0;
	while (in_arr[i])
	{
		qp = new_qp(in_arr[i]);
		if (has_unquoted_star(in_arr[i]))
		{
			matches = get_matches(qp->str, qp->mask);
			if (matches)
			{
				arr = merge_arr(arr, matches);
				free(qp->str);
				free(qp->mask);
				free(qp);
				i++;
				continue ;
			}
		}
		arr = append_arr(arr, qp->str);
		free(qp->mask);
		free(qp);	
		i++;
	}
	return (arr);
}

//! Ternary operator
static int	match_pattern(const char *pat, const char *mask, const char *str)
{
	if (!*pat)
		return (*str == '\0');

	if (*pat == '*' && (!mask || *mask == 0))
	{
		// Unquoted '*': try to match 0 or more characters
		return (match_pattern(pat + 1, mask ? mask + 1 : NULL, str)
			|| (*str && match_pattern(pat, mask, str + 1)));
	}

	// Quoted * or normal character match
	if (*pat == *str)
		return match_pattern(pat + 1, mask ? mask + 1 : NULL, str + 1);

	return 0;
}

