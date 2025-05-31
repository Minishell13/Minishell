/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:39:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 16:31:12 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

# include "typedef.h"

// EXIT
int		track_fd(int fd);
int		track_dup(int oldfd);
int		track_pipe(int pipefd[2]);
void	close_all_tracked_fds(void);

// Utils
t_bool	check_access(char *file, int permission);
char	*parse_path(char **all_path, char *cmd);
char	*get_path(char *cmd);

// Cmd Helper
void	execve_helper(t_ast *root, t_ast *cmd);

// Execution
void	execute_simple_cmd(t_ast *root, t_ast *node, t_bool no_fork);
void	execute_pipeline(t_ast *root, t_ast *node);
void	execute_redirection(t_ast *node);
void	execute_subshell(t_ast *root, t_ast *node);
void	execute_and_or(t_ast *root, t_ast *node);
void	executor(t_ast *root, t_ast *node);

#endif