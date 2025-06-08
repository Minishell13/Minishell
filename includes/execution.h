/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:39:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 22:10:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "typedef.h"

// Utils
char	*get_path(char *cmd);

// PIPE Helper
void	setup_pipe(int i, t_bool has_next);
void	redirect_pipes(int i, t_bool has_next);
void	close_pipes_in_child(int i, t_bool has_next);
void	close_pipes_in_parent(int i);
void	collect_pipeline_stages(t_ast *node, t_ast **stages, int *count);

// Execution
void	execute_simple_cmd(t_ast *node, t_bool no_fork);
void	execute_pipeline(t_ast *node);
t_bool	execute_redirection(t_ast *node);
void	execute_subshell(t_ast *node);
void	execute_and_or(t_ast *node);
void	run_executor(t_ast *node);
t_bool	executor(t_ast *node);

#endif
