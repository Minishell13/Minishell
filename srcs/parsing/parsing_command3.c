/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:53:52 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 13:02:28 by hwahmane         ###   ########.fr       */
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
	{
		g_sh.exit_code = FAILURE;
		return (false);
	}
	skip_empty_tokens(tokens);
	if (inner->sibling)
	{
		g_sh.exit_code = FAILURE;
		return (fdprintf(STDERR_FILENO ,S_E3), false);
	}
	if (!consume_token_type(tokens, TOKEN_CPARENTHES))
	{
		g_sh.exit_code = FAILURE;
		return (fdprintf(STDERR_FILENO ,S_E4), false);
	}
	*after_paren = *tokens;
	skip_empty_tokens(after_paren);
	if (*after_paren && (*after_paren)->type == TOKEN_OPARENTHES)
	{
		g_sh.exit_code = FAILURE;
		return (fdprintf(STDERR_FILENO ,S_E5), false);
	}
	return (true);
}

// ------------------- parse_complete_command
t_bool	is_invalid_start_token(t_token **tokens)
{
	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == TOKEN_CPARENTHES)
	{
		fdprintf(STDERR_FILENO ,S_E6);
		g_sh.exit_code = FAILURE;
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
		{
			g_sh.exit_code = FAILURE;
			fdprintf(STDERR_FILENO ,S_E6);
		}
		else
		{
			g_sh.exit_code = FAILURE;
			fdprintf(STDERR_FILENO ,S_E7);
		}
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

