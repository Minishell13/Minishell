/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:05:55 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/28 16:19:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_builtins(t_ast *node)
{
	char	*cmd;

	cmd = node->data.args[0];
	if (ft_strlcmp("cd", cmd))
		return (true);
	else if (ft_strlcmp("echo", cmd))
		return (true);
	else if (ft_strlcmp("env", cmd))
		return (true);
	else if (ft_strlcmp("exit", cmd))
		return (true);
	else if (ft_strlcmp("export", cmd))
		return (true);
	else if (ft_strlcmp("pwd", cmd))
		return (true);
	else if (ft_strlcmp("unset", cmd))
		return (true);
	return (false);
}

int	exec_builtins(t_ast *root, t_ast *node)
{
	char	*cmd;

	cmd = node->data.args[0];
	if (ft_strlcmp("cd", cmd))
	{
		expand_cmd_node(node, process_mode_1);	
		return (exec_cd(node));
	}
	else if (ft_strlcmp("echo", cmd))
	{
		expand_cmd_node(node, process_mode_1);	
		return (exec_echo(node));
	}
	else if (ft_strlcmp("env", cmd))
	{
		expand_cmd_node(node, process_mode_1);	
		return (exec_env(node));
	}
	else if (ft_strlcmp("exit", cmd))
	{
		expand_cmd_node(node, process_mode_1);	
		return (exec_exit(root, node));
	}
	else if (ft_strlcmp("export", cmd))
	{
		expand_cmd_node(node, process_mode_2);	
		return (exec_export(node));
	}
	else if (ft_strlcmp("pwd", cmd))
	{
		expand_cmd_node(node, process_mode_1);	
		return (exec_pwd(node));
	}
	else if (ft_strlcmp("unset", cmd))
	{
		expand_cmd_node(node, process_mode_1);	
		return (exec_unset(node));
	}
	return (EXIT_FAILURE);
}
