/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 15:33:33 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*parse_command(t_token **tokens)
{
	t_token	*after;
	t_token	*newpos;
	char	*bad;

	after = NULL;
	bad = NULL;
	newpos = NULL;
	if (!tokens || !*tokens)
		return (NULL);
	if (*tokens && ((*tokens)->type == TOKEN_OPARENTHES
			|| (*tokens)->type == TOKEN_CPARENTHES))
		return (parse_subshell(tokens, after, newpos, bad));
	return (parse_simple_command(tokens));
}

t_ast	*parse_pipe(t_token **tokens)
{
	t_ast	*left;

	left = parse_command(tokens);
	if (!left)
	{
		if ((*tokens) && ((*tokens)->type == TOKEN_PIPE
				|| (*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
			fdprintf(STDERR_FILENO, S_E, (*tokens)->value);
		return (NULL);
	}
	return (parse_pipe_loop(left, tokens));
}

t_ast	*parse_compound_command(t_token **tokens)
{
	t_ast			*left;
	t_ast			*right;
	t_bool			flag;
	t_token_type	op;

	flag = true;
	left = parse_pipe(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		op = (*tokens)->type;
		*tokens = (*tokens)->next;
		right = handle_compound_op(tokens, left, op);
		if (!right)
			return (free_tree(left), NULL);
		left = right;
		flag = false;
	}
	if (flag == true)
		return (left);
	return (right);
}

t_ast	*parse_command_list(t_token **tokens)
{
	t_ast	*head;
	t_ast	*cur;
	t_ast	*next;

	head = parse_compound_command(tokens);
	if (!head)
		return (NULL);
	cur = head;
	while (1)
	{
		while (*tokens && (*tokens)->type == TOKEN_EMPTY)
			*tokens = (*tokens)->next;
		next = parse_compound_command(tokens);
		if (!next)
			break ;
		tree_add_sibling(cur, next);
		cur = next;
	}
	return (head);
}

t_ast	*parse_complete_command(t_token **tokens)
{
	t_ast	*cmds;
	t_ast	*root;

	if (is_invalid_start_token(tokens))
	{
		g_sh.exit_code = FAILURE;
		return (NULL);
	}
	cmds = parse_command_list(tokens);
	if (!cmds || has_extra_tokens(tokens))
	{
		g_sh.exit_code = FAILURE;
		free_tree(cmds);
		return (NULL);
	}
	root = new_tree_node(GRAM_COMPLETE_COMMAND);
	if (!root)
	{
		g_sh.exit_code = FAILURE;
		free_tree(cmds);
		return (NULL);
	}
	tree_add_child(root, cmds);
	return (root);
}
