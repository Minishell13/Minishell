/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:39:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 13:27:37 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "typedef.h"

// Heredoc utils
t_bool	handle_heredocs(t_ast *root);

// File utils
t_bool	expand_and_redir(t_ast *node);

// Redirection Utils
int		track_fd(int fd);
int		track_dup(int oldfd);
void	save_fds(t_fd_backup *backup);
void	restore_fds(int stdin_backup, int stdout_backup);

#endif
