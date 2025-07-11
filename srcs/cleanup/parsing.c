/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:32:52 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/10 16:51:34 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
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
		else if (node->type == GRAM_HEREDOC)
		{
			if (g_sh.interactive)
				unlink(node->u_data.redir.file);
			free(node->u_data.redir.file);
			free(node->u_data.redir.limiter);
		}
		else if (node->type == GRAM_IO_REDIRECT
			|| node->type == GRAM_REDIR_IN
			|| node->type == GRAM_REDIR_OUT
			|| node->type == GRAM_REDIR_APPEND)
		{
			free(node->u_data.redir.file);
		}
		free_tree(node->child);
		free(node);
		node = next;
	}
}

void	free_all(void)
{
	if (g_sh.tokens)
		free_tokens(g_sh.tokens);
	if (g_sh.ast)
		free_tree(g_sh.ast);
	g_sh.tokens = NULL;
	g_sh.ast = NULL;
}
