/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:53:52 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/09 01:19:45 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// ------------------- parse_subshell functions
int	consume_token_type(t_token **tokens, t_token_type type)
{
	if (!*tokens || (*tokens)->type != type)
		return (0);
	*tokens = (*tokens)->next;
	return (1);
}

t_bool	check_subshell_errors(t_ast *inner, t_token **tokens,
		t_token **after_paren)
{
	if (!inner)
		return (printf("syntax error: empty subshell or invalid content\n"),
			false);
	skip_empty_tokens(tokens);
	if (inner->sibling)
		return (printf("syntax error: multiple commands in subshell\n"),
			false);
	if (!consume_token_type(tokens, TOKEN_CPARENTHES))
		return (printf("syntax error: expected ')'\n"), false);
	*after_paren = *tokens;
	skip_empty_tokens(after_paren);
	if (*after_paren && (*after_paren)->type == TOKEN_OPARENTHES)
		return (printf("syntax error: unexpected '('\n"), false);
	return (true);
}

// ------------------- parse_complete_command
t_bool	is_invalid_start_token(t_token **tokens)
{
	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == TOKEN_CPARENTHES)
	{
		printf("syntax error: unexpected ')'\n");
		return (true);
	}
	return (false);
}

t_bool	has_extra_tokens(t_token **tokens)
{
	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	if (*tokens)
	{
		if ((*tokens)->type == TOKEN_CPARENTHES)
			printf("syntax error: unexpected ')'\n");
		else
			printf("syntax error: unexpected token after command\n");
		return (true);
	}
	return (false);
}

// ------------------- parse_pipe
t_bool	is_invalid_pipe_token(t_token *token)
{
	return (!token
		|| token->type == TOKEN_CPARENTHES
		|| token->type == TOKEN_PIPE
		|| token->type == TOKEN_AND
		|| token->type == TOKEN_OR);
}
