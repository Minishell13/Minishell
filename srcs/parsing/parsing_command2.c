/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:36:09 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 15:33:53 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_empty_tokens(t_token **tokens)
{
	while (*tokens && (*tokens)->next && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
}

int	is_redirect_token(t_token *token)
{
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_HEREDOC);
}

t_ast	*create_redirect_node(t_token_type type, char *file, t_ast *list)
{
	t_ast	*op_node;

	if (!list)
		return (NULL);
	op_node = new_tree_leaf(GRAM_REDIR_IN + (type - TOKEN_REDIR_IN), file);
	if (!op_node)
		return (NULL);
	tree_add_child(list, op_node);
	return (list);
}

int	handle_redirection(t_token **tokens, t_ast *list)
{
	t_token_type	type;
	char			*file;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	skip_empty_tokens(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		fdprintf(STDERR_FILENO, R_E);
		return (0);
	}
	file = (*tokens)->value;
	*tokens = (*tokens)->next;
	if (!create_redirect_node(type, file, list))
		return (0);
	return (1);
}

t_ast	*handle_compound_op(t_token **tokens, t_ast *left, t_token_type op)
{
	t_ast	*right;

	if (!*tokens || (*tokens)->type == TOKEN_CPARENTHES
		|| (*tokens)->type == TOKEN_PIPE || (*tokens)->type == TOKEN_AND
		|| (*tokens)->type == TOKEN_OR)
	{
		fdprintf(STDERR_FILENO, C_E);
		return (NULL);
	}
	right = parse_pipe(tokens);
	if (!right)
		return (NULL);
	return (create_compound_node(left, right, op));
}
