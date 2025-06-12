/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:39:01 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/12 18:18:41 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_quoted_if_needed(int i, char *line, char *quot)
{
	if (line[i] == '\'' || line[i] == '"')
	{
		*quot = line[i];
		read_quoted_word(i, line);
	}
	return (i);
}

int	read_operator_if_needed(int i, char *line, t_token **head)
{
	if (line[i] == '&' && line[i + 1] == line[i])
	{
		i = operators(i, line, head);
		return (i);
	}
	return (-1);
}

int	read_word_loop(int i, char *line)
{
	char	quote;

	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && (is_operator_char(line[i]) || line[i] == ' '
				|| (line[i] >= 9 && line[i] <= 13)))
			break ;
		i++;
	}
	return (i);
}

int	handle_quotation_end(int i, char quot, char *line)
{
	if (quot && line[i--] != quot)
	{
		while (line[i] && line[i] != quot)
			i++;
		if (line[i] == quot)
			i++;
	}
	return (i);
}

// !------------------- this is parsing_subshill function
t_ast	*parse_subshell_redirs(t_token **tokens, t_ast *inner,
		t_ast **redir_list)
{
	*redir_list = NULL;
	while (*tokens && is_redirect_token(*tokens))
	{
		if (!*redir_list)
		{
			*redir_list = new_tree_node(GRAM_IO_REDIRECT);
			if (!*redir_list)
				return (NULL);
			tree_add_sibling(inner, *redir_list);
		}
		if (!handle_redirection(tokens, *redir_list))
			return (NULL);
	}
	if (*tokens && (*tokens)->type != TOKEN_EMPTY
		&& !is_redirect_token(*tokens))
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			printf("syntax error near unexpected token `%s'\n",
				(*tokens)->value);
			return (NULL);
		}
	}
	return ((t_ast *)1);
}
