/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:28:09 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/30 17:38:49 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token_type	get_token_type(char *str)
{
	if (str == NULL || *str == '\0')
		return (TOKEN_EMPTY);
	else if (ft_strncmp(str, "(", ft_strlen(str)) == 0)
		return (TOKEN_OPARENTHES);
	else if (ft_strncmp(str, ")", ft_strlen(str)) == 0)
		return (TOKEN_CPARENTHES);
	else if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (TOKEN_REDIR_OUT);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (TOKEN_REDIR_IN);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (TOKEN_AND);
	else if (ft_strncmp(str, "||", ft_strlen(str)) == 0)
		return (TOKEN_OR);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (TOKEN_REDIR_APPEND);
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

t_token *create_token(char *value)
{
    t_token *token;

    if (!value)
        return (NULL);
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = ft_strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->type = get_token_type(value);
    token->next = NULL;
    return (token);
}

void token_add_back(t_token **head, t_token *new_token)
{
    t_token *tmp;

    if (!new_token)
        return;
    if (!*head)
    {
        *head = new_token;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_token;
}

t_bool	has_unclosed_quotes(char *line)
{
	char	quote;

	quote = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '"')
		{
			if (!quote)
				quote = *line;
			else if (quote == *line)
				quote = 0;
		}
		line++;
	}
	if (quote)
	{
		printf("syntax error: unclosed quote `%c`\n", quote);
		return (true);
	}
	return (false);
}

int	read_quoted_word(int i, char *line)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] != quote)
	{
		fprintf(stderr, "syntax error: unclosed quote `%c`\n", quote);
		return (-1);
	}
	i++;
	return (i);
}
