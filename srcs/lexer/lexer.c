/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:00:23 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 11:32:22 by hwahmane         ###   ########.fr       */
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

// int	read_word(int i, char *line, t_token **head)
// {
// 	int		start;
// 	char	*word;
// 	char	quot;
// 	int		j;

// 	quot = '\0';
// 	i = read_quoted_if_needed(i, line, &quot);
// 	j = read_operator_if_needed(i, line, head);
// 	if (j != -1)
// 		return (j);
// 	start = i;
// 	i = read_word_loop(i, line);
// 	i = handle_quotation_end(i, quot, line);
// 	if (line[i] == '\n')
// 		line[i] = '\0';
// 	word = ft_substr(line, start, i - start);
// 	if (!word)
// 		return (-1);
// 	token_add_back(head, create_token(word));
// 	free(word);
// 	return (i);
// }
int	read_word(int i, char *line, t_token **head)
{
	char	*word;
	char	*part;
	int		start;
	char	quote;

	word = ft_strdup("");
	part = NULL;
	if (!word)
		return (-1);
	while (line[i] && !is_operator_char(line[i]) && line[i] != ' ' &&
		(line[i] < 9 || line[i] > 13))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			start = i++;
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
			{
				fdprintf(STDERR_FILENO, L_E, quote);
				g_sh.exit_code = FAILURE;
				free(word);
				return (-1);
			}
			i++;
			part = ft_substr(line, start, i - start);
		}
		else
		{
			start = i;
			while (line[i] && line[i] != '"' && line[i] != '\'' &&
				!is_operator_char(line[i]) && line[i] != ' ' &&
				(line[i] < 9 || line[i] > 13))
				i++;
			part = ft_substr(line, start, i - start);
		}
		if (!part)
		{
			free(word);
			return (-1);
		}
		char *tmp = word;
		word = ft_strjoin(word, part);
		free(tmp);
		free(part);
		if (!word)
			return (-1);
	}
	if (word && *word)
		token_add_back(head, create_token(word));
	free(word);
	return (i);
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
