/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:00:23 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 14:35:08 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '(' || c == ')');
}

int	operators(int i, char *line, t_token **head)
{
	int		start;
	char	*word;

	if (line[i] == '\0')
		return (i);
	start = i;
	if (line[i + 1] && line[i + 1] == line[i] && !(line[i] == '('
			|| line[i] == ')'))
		i++;
	i++;
	word = ft_substr(line, start, i - start);
	if (!word)
		return (-1);
	token_add_back(head, create_token(word));
	free(word);
	if (line[i] == '\n')
		line[i] = '\0';
	return (i);
}

int	read_word(int i, char *line, t_token **head)
{
	char	*word;
	char	*part;
	char	quote;

	word = ft_strdup("");
	if (!word)
		return (-1);
	while (line[i] && !is_operator_char(line[i]) && line[i] != ' '
		&& (line[i] < 9 || line[i] > 13))
	{
		part = NULL;
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			if (handle_quoted_part(&i, line, quote, &part) < 0)
				return (free(word), -1);
		}
		else if (handle_unquoted_part(&i, line, &part) < 0)
			return (free(word), -1);
		if (concat_part(&word, part) < 0)
			return (-1);
	}
	if (word && *word)
		token_add_back(head, create_token(word));
	return (free(word), i);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*head;

	if (has_unclosed_quotes(line))
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (is_operator_char(line[i]))
			i = operators(i, line, &head);
		else
		{
			if (line[i] != '\0')
				i = read_word(i, line, &head);
		}
		if (i == -1)
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
