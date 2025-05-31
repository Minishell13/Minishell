/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:13:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 20:13:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *ast_new_node(t_gram type)
{
	t_ast *n = ft_calloc(1, sizeof *n);
	if (!n) return NULL;

	n->type    = type;
	n->child   = NULL;
	n->sibling = NULL;

	// init union
	n->data.args           = NULL;
	n->data.redir.file     = NULL;
	n->data.redir.limiter  = NULL;
	n->data.redir.expanded = false;

	return n;
}

int ast_add_child(t_ast *p, t_ast *c)
{
	if (!p || !c) return -1;
	if (!p->child) {
		p->child = c;
	} 
	else {
		t_ast *it = p->child;
		while (it->sibling)
			it = it->sibling;
		it->sibling = c;
	}
	return 0;
}

// Returns an array of words split on any isspace(). Caller must free.
char	**ast_create_args(const char *s)
{
	if (!s) return NULL;

	// 1) Count how many words
	int count = 0;
	const char *p = s;
	while (*p) {
		// skip whitespace
		while (*p && isspace((unsigned char)*p)) p++;
		if (!*p) break;
		// at start of word
		count++;
		// skip non-whitespace
		while (*p && !isspace((unsigned char)*p)) p++;
	}

	// 2) Allocate array
	char **args = calloc(count + 1, sizeof *args);
	if (!args) return NULL;

	// 3) Extract each word
	p = s;
	for (int i = 0; i < count; i++) {
		// skip whitespace
		while (*p && isspace((unsigned char)*p)) p++;
		// start of word
		const char *start = p;
		while (*p && !isspace((unsigned char)*p)) p++;
		size_t len = p - start;
		args[i] = strndup(start, len);
		if (!args[i]) {
			// cleanup on failure
			for (int j = 0; j < i; j++) free(args[j]);
			free(args);
			return NULL;
		}
	}
	args[count] = NULL;
	return args;
}

void    ast_destroy(t_ast *n)
{
	if (!n) return;

	// destroy entire child subtree
	ast_destroy(n->child);

	// free this node’s payload
	if (n->type == GRAM_SIMPLE_COMMAND && n->data.args)
		clear_arr(n->data.args);
	else if ((n->type == GRAM_REDIR_IN
		   || n->type == GRAM_REDIR_OUT
		   || n->type == GRAM_REDIR_APPEND
		   || n->type == GRAM_HEREDOC)
		  && n->data.redir.file)
	{
		if (n->type == GRAM_HEREDOC)
			unlink(n->data.redir.file);
		free(n->data.redir.file);
		if (n->data.redir.limiter)
			free(n->data.redir.limiter);
	}
	// keep going with siblings
	ast_destroy(n->sibling);
	free(n);
}
