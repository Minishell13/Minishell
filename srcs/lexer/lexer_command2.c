/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:39:01 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 14:48:51 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_quoted_part(int *i, char *line, char quote, char **part)
{
	int	start;

	start = (*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		fdprintf(STDERR_FILENO, L_E, quote);
		return (-1);
	}
	(*i)++;
	*part = ft_substr(line, start, *i - start);
	if (!*part)
		return (-1);
	return (0);
}

int	handle_unquoted_part(int *i, char *line, char **part)
{
	int	start;

	start = *i;
	while (line[*i] && line[*i] != '"' && line[*i] != '\''
		&& !is_operator_char(line[*i]) && line[*i] != ' ' && (line[*i] < 9
			|| line[*i] > 13))
		(*i)++;
	*part = ft_substr(line, start, *i - start);
	if (!*part)
		return (-1);
	return (0);
}

int	concat_part(char **word, char *part)
{
	char	*tmp;

	tmp = *word;
	*word = ft_strjoin(*word, part);
	free(tmp);
	free(part);
	if (!*word)
		return (-1);
	return (0);
}
