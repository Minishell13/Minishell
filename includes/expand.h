/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:31:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:10:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "typedef.h"

// Expand Heredoc
t_bool	containe_quotes(char *s);
t_error	remove_quotes(t_redir *r);
t_error	expand_herdoc(t_redir *r, char **line);

// Expand Var Utils
t_quote	is_quote(char c);
int		is_valid(char c);
char	*extract_var_value(char *arg, int *i);
t_bool	try_expand_dollar(char *arg, char **value, int *i);

// Expand Var
void	default_mode(char *arg, char **v, int *i);
void	expand_mode(char *arg, char **v, int *i);
void	literal_mode(char *arg, char **v, int *i);
void	append_args(char ***arr, char **v, t_bool split);
t_bool	process_mode(char *arg, t_qmode mode, t_expand_ctx *ctx);
char	**expand_vars_arr(char *arg);

void	expand_cmd_node(t_ast *node);
t_bool	expand_redir(t_ast *node);

// Expand Wildcard *
void	fill_qp(char *arg, t_qp *qp);
t_qp	*create_qp(char *arg);

t_bool	has_unquoted_star(const char *s);
int		match_pattern(const char *pat, const char *mask, const char *str);
int		count_matches(const char *pat, const char *mask);
char	**get_matches(const char *pat, const char *mask);
char	**wildcard_expand_arr(char **in_arr);

#endif
