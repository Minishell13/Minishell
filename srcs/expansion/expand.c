/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/04 14:09:24 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**expand_vars_arr(char *arg)
{
	int				i;
	char			*value;
	char			**arr;
	t_qmode			mode;
	t_expand_ctx	ctx;

	i = 0;
	mode = DEFAULT;
	arr = init_arr();
	if (!arr)
		return (NULL);
	ctx.arr = &arr;
	ctx.v = &value;
	ctx.i = &i;
	while (arg[i])
	{
		if (is_quote(arg[i]) == SINGLE_Q)
			mode = LITERAL;
		else if (is_quote(arg[i]) == DOUBLE_Q)
			mode = EXPAND;
		else
			mode = DEFAULT;
		value = ft_strdup("");
		if (process_mode(arg, mode, &ctx))
			continue ;
		i++;
	}
	return (arr);
}



// char	**expand_vars_arr(char *arg)
// {
// 	int				i;
// 	char			*value;
// 	char			**arr;
// 	t_qmode	mode;
	
// 	i = 0;
// 	mode = DEFAULT;
// 	arr = init_arr();
// 	if (!arr)
// 		return (NULL);
// 	while (arg[i])
// 	{
// 		if (is_quote(arg[i]) == SINGLE_Q)
// 			mode = LITERAL;
// 		else if (is_quote(arg[i]) == DOUBLE_Q)
// 			mode = EXPAND;
// 		else
// 			mode = DEFAULT;
// 		value = ft_strdup("");
// 		if (process_mode(arg, mode, &arr, &value, &i))
// 			continue ;
// 		i++;
// 	}
// 	return (arr);
// }

t_bool	expand_redir(t_ast *node)
{
	char	**parts;
	char	**with_glob;

	if (node->type == GRAM_HEREDOC)
		remove_quotes(&(node->u_data.redir));
	else
	{
		parts = expand_vars_arr(node->u_data.redir.file);
		with_glob = wildcard_expand_arr(parts);
		clear_arr(parts);
		int	len = len_arr(with_glob);
		if (len != 1)
		{
			fdprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
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

void expand_cmd_node(t_ast *cmd)
{
	char	**new_args;
	int		i;

    new_args = init_arr();
	i = 0;
    while (cmd->u_data.args[i])
    {
        char **parts    = expand_vars_arr(cmd->u_data.args[i]);
        char **with_glob = wildcard_expand_arr(parts);
        clear_arr(parts);
        new_args = merge_arr(new_args, with_glob);
		i++;
    }
    clear_arr(cmd->u_data.args);
    cmd->u_data.args = new_args;
}

