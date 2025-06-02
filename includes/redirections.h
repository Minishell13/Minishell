/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:39:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 13:01:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
#define REDIRECTIONS_H

# include "typedef.h"

// Heredoc utils
void	generate_tmpfile(t_redir *redir);
void	fill_here_doc(t_redir *redir, int fd);
int		here_doc(t_redir *redir);
t_bool	handle_heredocs(t_ast *root);

// File utils
int		parse_infile(t_redir *redir, t_gram type);
int		parse_outfile(t_redir *redir, t_gram type);
// void	redir(t_redir *r, t_gram type);
t_bool	redir(t_redir *r, t_gram type);
// void	expand_and_redir(t_ast *node);
t_bool	expand_and_redir(t_ast *node);

// Redirection Utils
void	restore_fds(int stdin_backup, int stdout_backup);

#endif
