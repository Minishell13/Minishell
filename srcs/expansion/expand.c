/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/12 18:14:51 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**expand_dollar(char *arg)
{
	t_qmode			mode;
	t_expand_ctx	ctx;

	mode = DEFAULT;
	ctx.arr = init_arr();
	if (!ctx.arr)
		return (NULL);
	ctx.i = 0;
	while (arg[ctx.i])
	{
		if (is_quote(arg[ctx.i]) == SINGLE_Q)
			mode = LITERAL;
		else if (is_quote(arg[ctx.i]) == DOUBLE_Q)
			mode = EXPAND;
		else
			mode = DEFAULT;
		ctx.v = ft_strdup("");
		if (expand_var(arg, mode, &ctx))
			continue ;
		ctx.i++;
	}
	return (ctx.arr);
}

t_bool	expand_redir_node(t_ast *node)
{
	char	**parts;
	char	**with_glob;

	if (node->type == GRAM_HEREDOC)
		remove_quotes(&(node->u_data.redir));
	else
	{
		parts = expand_dollar(node->u_data.redir.file);
		with_glob = expand_wildcard(parts);
		clear_arr(parts);
		if (len_arr(with_glob) != 1)
		{
			fdprintf(STDERR_FILENO, TOO_REDIR,
				g_sh.shell, node->u_data.redir.file);
			return (clear_arr(with_glob), false);
		}
		else
		{
			free(node->u_data.redir.file);
			node->u_data.redir.file = ft_strdup(with_glob[0]);
			clear_arr(with_glob);
		}
	}
	return (true);
}

void	expand_cmd_node(t_ast *cmd)
{
	char	**new_args;
	int		i;
	char	**parts;
	char	**with_glob;

	new_args = init_arr();
	i = 0;
	while (cmd->u_data.args[i])
	{
		parts = expand_dollar(cmd->u_data.args[i]);
		with_glob = expand_wildcard(parts);
		clear_arr(parts);
		new_args = merge_arr(new_args, with_glob);
		i++;
	}
	clear_arr(cmd->u_data.args);
	cmd->u_data.args = new_args;
}
