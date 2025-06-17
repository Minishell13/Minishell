/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:36:33 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 15:34:17 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*handle_pipe_error(t_ast *left)
{
	free_tree(left);
	fdprintf(STDERR_FILENO, P_E);
	g_sh.exit_code = FAILURE;
	return (NULL);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*pipe;

	pipe = new_tree_node(GRAM_PIPE);
	if (!pipe)
	{
		free_tree(left);
		free_tree(right);
		return (NULL);
	}
	tree_add_child(pipe, left);
	tree_add_child(pipe, right);
	return (pipe);
}

t_ast	*parse_pipe_loop(t_ast *left, t_token **tokens)
{
	t_ast	*right;
	t_ast	*pipe;

	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (is_invalid_pipe_token(*tokens))
			return (handle_pipe_error(left));
		right = parse_command(tokens);
		if (!right)
		{
			free_tree(left);
			return (NULL);
		}
		pipe = create_pipe_node(left, right);
		if (!pipe)
			return (NULL);
		left = pipe;
	}
	return (left);
}

void	free_parse_data(t_parse_data *data, int free_rlist)
{
	free(data->cmd);
	free_list(data->words);
	if (free_rlist)
		free(data->rlist);
}

int	handle_parse_errors(t_token **tokens, t_parse_data *data)
{
	if (!collect_words_and_redirects(tokens, data))
	{
		free_parse_data(data, 1);
		return (0);
	}
	if (has_subshell_error(tokens))
	{
		free_parse_data(data, 0);
		return (0);
	}
	if (data->flag && !fill_args(data->cmd, data->words))
	{
		free_parse_data(data, 0);
		return (0);
	}
	return (1);
}
