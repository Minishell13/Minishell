/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	has_unquoted_star(const char *s)
{
	int		i;
	t_quote	state;

	i = 0;
	state = NONE;
	while (s[i])
	{
		if (s[i] == '\'' && state == NONE)
			state = SINGLE_Q;
		else if (s[i] == '\'' && state == SINGLE_Q)
			state = 0;
		else if (s[i] == '"' && state == NONE)
			state = DOUBLE_Q;
		else if (s[i] == '"' && state == DOUBLE_Q)
			state = 0;
		else if (s[i] == '*' && state == NONE)
			return (true);
		i++;
	}
	return (false);
}

int	match_pattern(const char *pat, const char *mask, const char *str)
{
	// Check if the pat is ended, and look if also the str is done (we know now if the str match the pat or not)
	if (!*pat)
		return (*str == '\0');
	// We try to conusme * against str (until pat + 1 == str) so the * is consumed
	if (*pat == '*' && (!mask || *mask == 0))
	{
		if (mask && *mask != '\0')
			mask++;
		return (match_pattern(pat + 1, mask, str)
			|| (*str && match_pattern(pat, mask, str + 1)));
	}
	// Both pat and str have same char so thet s go ahead and advance all three 
	if (*pat == *str)
	{
		if (mask && *mask != '\0')
			mask++;
		return (match_pattern(pat + 1, mask, str + 1));
	}

	return (0);
}

int	count_matches(const char *pat, const char *mask)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				count;

	count = 0;
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent)
	{
		if (dirent->d_name[0] != '.' && match_pattern(pat, mask, dirent->d_name))
			count++;
		dirent = readdir(dir);
	}
	closedir(dir);
	return (count);
}

char	**get_matches(const char *pat, const char *mask)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				count;
	int				idx;
	char			**matches;

	count = count_matches(pat, mask);
	if (count == 0)
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
		if (dirent->d_name[0] != '.' && match_pattern(pat, mask, dirent->d_name))
			matches[idx++] = ft_strdup(dirent->d_name);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

char	**wildcard_expand_arr(char **in_arr)
{
	char	**arr;
	char	**matches;
	int		i;
	t_qp	*qp;

	arr = init_arr();
	i = 0;
	while (in_arr[i])
	{
		qp = create_qp(in_arr[i]);
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
