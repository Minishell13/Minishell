/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_merge_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 11:44:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **append_arr(char **arr, char *str)
{
	size_t old_len;
	char **new_arr;

	old_len = len_arr(arr);
	new_arr = (char **) ft_realloc(arr, sizeof(char*) * (old_len + 1)
				, sizeof(char*) * (old_len + 2));
	if (!new_arr)
		return (free(str), NULL);
	new_arr[old_len]     = str;
	new_arr[old_len + 1] = NULL;
	return (new_arr);
}

static char	**dup_but_last(char **arr)
{
	char	**new;
	size_t	len;
	size_t	i;

	len = len_arr(arr);
	if (len == 0 || !arr)
		return (ft_calloc(1, sizeof(char *)));
	new = ft_calloc(len + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

static char	*merge_edges(char *last1, char *first2, char **arr1, char **arr2)
{
	char	*merged;

	merged = ft_strjoin(last1, first2);
	if (!merged)
	{
		clear_arr(arr1);
		clear_arr(arr2);
	}
	return (merged);
}

static char	**append_rest(char **out, char **arr2)
{
	size_t	i;

	i = 1;
	while (arr2[i])
	{
		out = append_arr(out, ft_strdup(arr2[i]));
		if (!out)
		{
			clear_arr(arr2);
			return (NULL);
		}
		i++;
	}
	return (out);
}

char	**inner_merge_arr(char **arr1, char **arr2)
{
	size_t	lens[2];
	char	**out;
	char	*edge;

	lens[0] = len_arr(arr1);
	lens[1] = len_arr(arr2);
	if (lens[0]  == 0 && lens[1] == 0)
		return (clear_arr(arr2), arr1);
	if (lens[0]  == 0)
		return (clear_arr(arr1), arr2);
	if (lens[1] == 0)
		return (clear_arr(arr2), arr1);
	out = dup_but_last(arr1);
	edge = merge_edges(arr1[lens[0]  - 1], arr2[0], arr1, arr2);
	if (!edge)
		return (NULL);

	out = append_arr(out, edge);
	if (!out)
		return (free(edge), clear_arr(arr2), NULL);

	out = (char **)append_rest(out, arr2);
	if (!out)
		return (NULL);
	return (clear_arr(arr1), clear_arr(arr2), out);
}
