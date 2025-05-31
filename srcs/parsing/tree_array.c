/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:00:51 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/31 20:17:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create an internal node (no string)
t_ast	*new_tree_node(t_gram gram)
{
	t_ast	*n;

	n = malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->type = gram;
	n->child = NULL;
	n->sibling = NULL;
	n->data.args = NULL;
	n->data.redir.file = NULL;
	n->data.redir.expanded = false;
	return (n);
}

// create a leaf node (a WORD or filename)
t_ast	*new_tree_leaf(t_gram gram, char *s)
{
	t_ast	*n;
	int		len;

	len = 0;
	n = new_tree_node(gram);
	if (!n)
		return (NULL);
	n->data.redir.file = strdup(s);
	len = ft_strlen(n->data.redir.file);
	if (gram == GRAM_HEREDOC && (n->data.redir.file[0] != '"'
			&& n->data.redir.file[0] != '\'')
		&& (n->data.redir.file[len - 1] != '"'
			&& n->data.redir.file[len - 1] != '\''))
		n->data.redir.expanded = true;
	return (n);
}

// append `c` as the last child of `parent`
void	tree_add_child(t_ast *parent, t_ast *c)
{
	t_ast	*it;

	if (!parent || !c)
		return ;
	if (!parent->child)
	{
		parent->child = c;
	}
	else
	{
		it = parent->child;
		while (it->sibling)
			it = it->sibling;
		it->sibling = c;
	}
}

// append `sib` as the last sibling of `node`
void	tree_add_sibling(t_ast *node, t_ast *sib)
{
	if (!node || !sib)
		return ;
	while (node->sibling)
		node = node->sibling;
	node->sibling = sib;
}

// Append a node to the list
void	append_to_list(t_list **list, t_list *new_node)
{
	t_list	*temp;

	if (!*list)
	{
		*list = new_node;
	}
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
