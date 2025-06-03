/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:32:52 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 10:47:20 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void free_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		tmp = list->next;
		free(list);  // only free the list node itself
		list = tmp;
	}
}

void	free_tree(t_ast *node)
{
	t_ast	*next;

	while (node)
	{
		next = node->sibling;

		if (node->type == GRAM_SIMPLE_COMMAND)
			free_string_array(node->u_data.args);

		if ((node->type == GRAM_IO_REDIRECT
			 || node->type == GRAM_REDIR_IN
			 || node->type == GRAM_REDIR_OUT
			 || node->type == GRAM_REDIR_APPEND
			 || node->type == GRAM_HEREDOC))
			free(node->u_data.redir.file);

		free_tree(node->child); // this will handle child + its siblings
		free(node);
		node = next;
	}
}

void	free_all()
{
	if (sh.tokens)
		free_tokens(sh.tokens);
	if (sh.ast)
		free_tree(sh.ast);
	sh.tokens = NULL;
	sh.ast = NULL;
}
