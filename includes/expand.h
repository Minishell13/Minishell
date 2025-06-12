/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:31:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/12 16:51:56 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "typedef.h"

// Expand Heredoc
t_bool	containe_quotes(char *s);
t_bool	remove_quotes(t_redir *r);
t_bool	expand_herdoc(t_redir *r, char **line);

// Expand Var Utils
t_quote	is_quote(char c);
// int		is_valid(char c);
// char	*extract_var_value(char *arg, int *i);
t_bool	try_expand_dollar(char *arg, char **value, int *i);

// Expand Var
void	default_mode(char *arg, char **v, int *i);
void	expand_mode(char *arg, char **v, int *i);
void	literal_mode(char *arg, char **v, int *i);
void	append_args(char ***arr, char **v, t_bool split);
t_bool	expand_var(char *arg, t_qmode mode, t_expand_ctx *ctx);
char	**expand_dollar(char *arg);

// Expand Node
void	expand_cmd_node(t_ast *node);
t_bool	expand_redir_node(t_ast *node);

// Expand Wildcard *
t_bool	has_unquoted_star(const char *s);
void	fill_qp(char *arg, t_qp *qp);
t_qp	*new_qp(char *arg);
t_qp	**create_qps(char **in_arr);
void	clear_qps(t_qp **qps);
char	**expand_wildcard(char **in_arr);

#endif
