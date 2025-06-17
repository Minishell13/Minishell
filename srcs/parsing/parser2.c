/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:44:16 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 11:27:22 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*parse_subshell(t_token **tokens, t_token *after)
{
	t_ast	*node;
	t_ast	*inner;
	t_ast	*redir_list;
	t_token	*after_paren;

    if (check_nested_empty(*tokens, &after)) {
        *tokens = after;
		fdprintf(STDERR_FILENO, S_E2);
		g_sh.exit_code = FAILURE;
        return NULL;
    }
	if (!consume_token_type(tokens, TOKEN_OPARENTHES))
		return (NULL);
	skip_empty_tokens(tokens);
	inner = parse_command_list(tokens);
	if (!check_subshell_errors(inner, tokens, &after_paren))
	{
		free_tree(inner);
		return (NULL);
	}
	node = new_tree_node(GRAM_SUBSHELL);
	if (!node)
		return (NULL);
	tree_add_child(node, inner);
	if (!parse_subshell_redirs(tokens, inner, &redir_list))
		return (NULL);
	return (node);
}

t_bool	handle_redirect(t_token **tokens, t_ast **rlist, t_ast *cmd,
		t_bool flag)
{
	if (flag && !*rlist)
	{
		*rlist = new_tree_node(GRAM_IO_REDIRECT);
		if (!*rlist)
			return (false);
	}
	if (flag)
	{
		if (!handle_redirection(tokens, *rlist))
			return (false);
	}
	else
	{
		if (!handle_redirection(tokens, cmd))
			return (false);
	}
	return (true);
}

t_bool	collect_words_and_redirects(t_token **tokens, t_parse_data *data)
{
	t_list	*last;
	t_list	*new_word;

	last = NULL;
	while (*tokens && (is_redirect_token(*tokens)
			|| (*tokens)->type == TOKEN_WORD))
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			new_word = malloc(sizeof(t_list));
			if (!new_word)
				return (false);
			new_word->token = *tokens;
			new_word->next = NULL;
			if (!data->words)
				data->words = new_word;
			else
				last->next = new_word;
			last = new_word;
			*tokens = (*tokens)->next;
		}
		else if (!handle_redirect(tokens, &data->rlist, data->cmd, data->flag))
			return (false);
	}
	return (true);
}

t_bool	find_command_type(t_token **tokens, t_ast **cmd)
{
	t_token	*cursor;

	cursor = *tokens;
	while (cursor)
	{
		if (is_redirect_token(cursor))
		{
			cursor = cursor->next;
			if (cursor && cursor->type == TOKEN_WORD)
				cursor = cursor->next;
		}
		else if (cursor->type == TOKEN_WORD)
		{
			*cmd = new_tree_node(GRAM_SIMPLE_COMMAND);
			return (true);
		}
		else
			break ;
	}
	if (is_redirect_token(*tokens))
		*cmd = new_tree_node(GRAM_IO_REDIRECT);
	return (false);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_parse_data	data;

	data.rlist = NULL;
	data.words = NULL;
	data.cmd = NULL;
	data.flag = find_command_type(tokens, &data.cmd);
	if (!data.cmd)
		return (NULL);
	if (!collect_words_and_redirects(tokens, &data))
	{
		free(data.cmd);
		free_list(data.words);
		return (NULL);
	}
	if (has_subshell_error(tokens))
	{
		free(data.cmd);
		free_list(data.words);
		return (NULL);
	}
	if (data.flag && !fill_args(data.cmd, data.words))
	{
		free(data.cmd);
		free_list(data.words);
		return (NULL);
	}
	free_list(data.words);
	if (data.flag)
		tree_add_child(data.cmd, data.rlist);
	return (data.cmd);
}
