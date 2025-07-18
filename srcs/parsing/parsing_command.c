/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:28:52 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 15:33:46 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_words(t_list *word_list)
{
	int	count;

	count = 0;
	while (word_list)
	{
		count++;
		word_list = word_list->next;
	}
	return (count);
}

int	fill_words_array(char **arr, t_list *word_list)
{
	int	i;

	i = 0;
	while (word_list)
	{
		arr[i] = strdup(word_list->token->value);
		if (!arr[i])
			return (0);
		i++;
		word_list = word_list->next;
	}
	arr[i] = NULL;
	return (1);
}

t_list	*collect_words(t_token **tokens)
{
	t_list	*list;
	t_list	*new;

	list = NULL;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new->token = *tokens;
		new->next = NULL;
		append_to_list(&list, new);
		*tokens = (*tokens)->next;
	}
	return (list);
}

t_bool	fill_args(t_ast *cmd, t_list *words)
{
	int	count;

	if (!words)
		return (false);
	count = count_words(words);
	cmd->u_data.args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->u_data.args)
		return (false);
	if (!fill_words_array(cmd->u_data.args, words))
		return (false);
	return (true);
}

t_bool	has_subshell_error(t_token **tokens)
{
	t_token	*after;
	t_token	*newpos;
	char	*bad;

	after = NULL;
	bad = NULL;
	newpos = NULL;
	if (*tokens && (*tokens)->type == TOKEN_OPARENTHES)
	{
		skip_empty_tokens(tokens);
		if ((*tokens)->next)
			fdprintf(STDERR_FILENO, S_E, (*tokens)->next->value);
		else
			parse_subshell(tokens, after, newpos, bad);
		return (true);
	}
	return (false);
}
