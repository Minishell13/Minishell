/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:34:25 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 15:34:11 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	check_nested_empty(t_token *start, t_token **after)
{
	t_token	*p;

	if (!start || start->type != TOKEN_OPARENTHES)
		return (false);
	p = start->next;
	while (p && p->type == TOKEN_EMPTY)
		p = p->next;
	if (!p)
		return (false);
	if ((!p->next && p->type == TOKEN_OPARENTHES)
		|| p->type == TOKEN_CPARENTHES)
	{
		*after = p->next;
		return (true);
	}
	else if (p->type == TOKEN_OPARENTHES)
		return (check_nested_empty(p, after));
	return (false);
}

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
			fdprintf(STDERR_FILENO, S_E, (*tokens)->value);
			return (NULL);
		}
	}
	return ((t_ast *)1);
}

t_bool	check_nested_invalid_after_paren(t_token *start, t_token **after,
		char **bad_val)
{
	t_token	*p;

	p = start;
	while (p && p->type == TOKEN_OPARENTHES)
	{
		p = p->next;
		while (p && p->type == TOKEN_EMPTY)
			p = p->next;
	}
	if (p && (p->type == TOKEN_PIPE || p->type == TOKEN_AND
			|| p->type == TOKEN_OR))
	{
		*bad_val = p->value;
		*after = p->next;
		return (true);
	}
	return (false);
}

t_ast	*create_compound_node(t_ast *left, t_ast *right, t_token_type op)
{
	t_ast	*node;
	t_gram	gram_type;

	if (op == TOKEN_AND)
		gram_type = GRAM_OPERATOR_AND;
	else
		gram_type = GRAM_OPERATOR_OR;
	node = new_tree_node(gram_type);
	if (!node)
	{
		free_tree(right);
		return (NULL);
	}
	tree_add_child(node, left);
	tree_add_child(node, right);
	return (node);
}
