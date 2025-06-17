/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:00:51 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 15:34:23 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*handle_subshell_error_case(t_token **tokens, t_token **pos, char *err,
		int error)
{
	*tokens = *pos;
	if (error == 0)
		fdprintf(STDERR_FILENO, S_E4);
	else
		fdprintf(STDERR_FILENO, S_E, err);
	g_sh.exit_code = FAILURE;
	return (NULL);
}

t_ast	*handle_subshell_parsing(t_token **tokens, t_ast *inner)
{
	t_ast	*node;
	t_ast	*redir_list;

	node = new_tree_node(GRAM_SUBSHELL);
	if (!node)
		return (NULL);
	tree_add_child(node, inner);
	if (!parse_subshell_redirs(tokens, inner, &redir_list))
		return (NULL);
	return (node);
}
