/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahmane <wahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/11 21:57:49 by wahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// parse command → subshell | simple_command
t_ast	*parse_command(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (*tokens && ((*tokens)->type == TOKEN_OPARENTHES
			|| (*tokens)->type == TOKEN_CPARENTHES))
		return (parse_subshell(tokens));
	return (parse_simple_command(tokens));
}

// parse pipeline: command ( '|' command )*
t_ast	*parse_pipe(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipe;

	left = parse_command(tokens);
	if (!left)
	{
		if ((*tokens) && ((*tokens)->type == TOKEN_PIPE
				|| (*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
			printf("syntax error near unexpected token `%s'", (*tokens)->value);
		return (NULL);
	}
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (is_invalid_pipe_token(*tokens))
		{
			free_tree(left);
			printf("syntax error: unexpected token after '|'\n");
			return (NULL);
		}
		right = parse_command(tokens);
		if (!right)
		{
			free_tree(right);
			return (NULL);
		}
		pipe = new_tree_node(GRAM_PIPE);
		tree_add_child(pipe, left);
		tree_add_child(pipe, right);
		left = pipe;
	}
	return (left);
}

// parse compound_command: pipeline ( (&& ||) pipeline )*
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
		{
			free_tree(left);
			return (NULL);
		}
		left = right;
		flag = false;
	}
	if (flag == true)
		return (left);
	return (right);
}

// parse command_list: compound_command ( compound_command )*
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
		return (NULL);
	cmds = parse_command_list(tokens);
	if (!cmds || has_extra_tokens(tokens))
	{
		free_tree(cmds);
		return (NULL);
	}
	root = new_tree_node(GRAM_COMPLETE_COMMAND);
	if (!root)
	{
		free_tree(cmds);
		return (NULL);
	}
	tree_add_child(root, cmds);
	return (root);
}
