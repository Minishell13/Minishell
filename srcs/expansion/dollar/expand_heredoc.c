/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:03:53 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/12 16:50:07 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	containe_quotes(char *s)
{
	if (ft_strchr(s, '\''))
		return (true);
	if (ft_strchr(s, '\"'))
		return (true);
	return (false);
}

t_bool	remove_quotes(t_redir *r)
{
	int		i;
	char	*value;
	char	*tmp;

	if (containe_quotes(r->limiter) == false)
		return (true);
	i = 0;
	value = ft_strdup("");
	while (r->limiter[i])
	{
		if (is_quote(r->limiter[i]))
		{
			i++;
			continue ;
		}
		tmp = ft_charjoin(value, r->limiter[i]);
		value = tmp;
		i++;
	}
	free(r->limiter);
	r->limiter = value;
	return (true);
}

t_bool	expand_herdoc(t_redir *r, char **line)
{
	int		i;
	char	*value;

	if (r->expanded == false)
		return (true);
	i = 0;
	value = ft_strdup("");
	if (!value)
		return (false);
	while ((*line)[i])
	{
		if (is_quote((*line)[i]))
		{
			value = ft_charjoin(value, (*line)[i]);
			if (!value)
				return (free(value), false);
			i++;
			continue ;
		}
		default_mode((*line), &value, &i);
	}
	free((*line));
	(*line) = value;
	return (true);
}
