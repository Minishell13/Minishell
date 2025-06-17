/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:00:51 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 15:34:35 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*new_tree_node(t_gram gram)
{
	t_ast	*n;

	n = malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->type = gram;
	n->child = NULL;
	n->sibling = NULL;
	n->u_data.args = NULL;
	n->u_data.redir.file = NULL;
	n->u_data.redir.limiter = NULL;
	n->u_data.redir.expanded = false;
	return (n);
}

t_ast	*new_tree_leaf(t_gram gram, char *s)
{
	t_ast	*n;
	int		len;

	len = 0;
	n = new_tree_node(gram);
	if (!n)
		return (NULL);
	if (gram == GRAM_HEREDOC)
	{
		generate_tmpfile(&n->u_data.redir);
		n->u_data.redir.limiter = strdup(s);
	}
	else
		n->u_data.redir.file = strdup(s);
	len = ft_strlen(n->u_data.redir.file);
	if (gram == GRAM_HEREDOC && !containe_quotes(n->u_data.redir.limiter))
		n->u_data.redir.expanded = true;
	return (n);
}

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

void	tree_add_sibling(t_ast *node, t_ast *sib)
{
	if (!node || !sib)
		return ;
	while (node->sibling)
		node = node->sibling;
	node->sibling = sib;
}

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
