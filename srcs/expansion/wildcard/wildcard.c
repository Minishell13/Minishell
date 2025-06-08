/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 21:44:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	match_star(const char *pat, const char *mask, const char *str);
static int	match_pattern(const char *pat, const char *mask, const char *str);

static int	match_star(const char *pat, const char *mask, const char *str)
{
	if (!pat || !str)
		return (0);
	while (*pat == '*' && (!mask || *mask == '\0' || *mask == '*'))
	{
		pat++;
		if (mask)
			mask++;
	}
	while (*str)
	{
		if (match_pattern(pat, mask, str))
			return (1);
		str++;
	}
	return (match_pattern(pat, mask, str));
}

static int	match_pattern(const char *pat, const char *mask, const char *str)
{
	const char	*next_mask;

	if (!*pat)
		return (*str == '\0');
	if (*pat == '*' && (!mask || *mask == '\0'))
		return (match_star(pat, mask, str));
	if (*pat == *str)
	{
		if (mask)
			next_mask = mask + 1;
		else
			next_mask = NULL;
		return (match_pattern(pat + 1, next_mask, str + 1));
	}
	return (0);
}

static int	count_matches(const char *pat, const char *mask)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	dirent = readdir(dir);
	while (dirent)
	{
		if (dirent->d_name[0] != '.'
			&& match_pattern(pat, mask, dirent->d_name))
			count++;
		dirent = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static char	**get_matches(const char *pat, const char *mask)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				count;
	int				idx;
	char			**matches;

	count = count_matches(pat, mask);
	if (count < 1)
		return (NULL);
	matches = (char **) ft_calloc(count + 1, sizeof(char *));
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (free(matches), NULL);
	idx = 0;
	dirent = readdir(dir);
	while (dirent)
	{
		if (dirent->d_name[0] != '.'
			&& match_pattern(pat, mask, dirent->d_name))
			matches[idx++] = ft_strdup(dirent->d_name);
		dirent = readdir(dir);
	}
	return (closedir(dir), matches);
}

char	**expand_wildcard(char **in_arr)
{
	char	**arr;
	char	**matches;
	t_qp	**qps;
	int		i;

	arr = init_arr();
	qps = create_qps(in_arr);
	if (!qps)
		return (arr);
	i = 0;
	while (qps[i])
	{
		if (has_unquoted_star(in_arr[i]))
		{
			matches = get_matches(qps[i]->str, qps[i]->mask);
			if (matches)
			{
				arr = merge_arr(arr, matches);
				i++;
				continue ;
			}
		}
		arr = append_arr(arr, ft_strdup(qps[i++]->str));
	}
	return (clear_qps(qps), arr);
}
