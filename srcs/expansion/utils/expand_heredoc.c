/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:03:53 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 13:24:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_minishell	sh;

t_bool	containe_quotes(char *s)
{
	if (ft_strchr(s, '\''))
		return (true);
	if (ft_strchr(s, '\"'))
		return (true);
	return (false);
}

t_error	remove_quotes(t_redir *r)
{
	int		i;
	char	*value;
	char	*tmp;

	// [Case 1] Don't containe quotes so can expand content
	if (containe_quotes(r->limiter) == false)
	{
		r->expanded = true;
		return (SUCCESS);
	}
	// [Case 2] Containe quotes so remove them and can't expand content
	i = 0;
	value = ft_strdup("");
	if (!value)
		return (MALLOC_ERROR);
	while (r->limiter[i])
	{
		if (is_quote(r->limiter[i]))
		{
			i++;
			continue ;
		}
		tmp = ft_charjoin(value, r->limiter[i]);
		if (!tmp)
			return (free(value), MALLOC_ERROR);
		value = tmp;
		i++;
	}
	free(r->limiter);
	r->limiter = value;
	return (SUCCESS);
}

t_error	expand_herdoc(t_redir *r, char **line)
{
	int		i;
	char	*value;

	if (r->expanded == false)
		return (SUCCESS);
	i = 0;
	value = ft_strdup("");
	if (!value)
		return (MALLOC_ERROR);
	while ((*line)[i])
	{
		if (is_quote((*line)[i]))
		{
			value = ft_charjoin(value, (*line)[i]);
			if (!value)
				return (free(value), MALLOC_ERROR);
			i++;
			continue ;
		}
		default_mode((*line), &value, &i);
	}
	free((*line));
	(*line) = value;
	return (SUCCESS);
}
