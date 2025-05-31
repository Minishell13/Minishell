/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:31:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 17:15:26 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

# include "typedef.h"

// Expand node
void	expand_cmd_node(t_ast *node, t_bool(*f)(char *, t_qmode, char ***, char **, int *));
// Expand Heredoc
t_bool	containe_quotes(char *s);
t_error remove_quotes(t_redir *r);
t_error	expand_herdoc(t_redir *r, char **line);

// Expand Redirection
void	expand_redir(t_ast *node);

// Expand Var
t_quote	is_quote(char c);
int	is_valid(char c);
char	*extract_var_value(char *arg, int *i);
t_bool	try_expand_dollar(char *arg, char **value, int *i);

void	default_mode(char *arg, char **v, int *i);
void	expand_mode(char *arg, char **v, int *i);
void	literal_mode(char *arg, char **v, int *i);
void	append_args(char ***arr, char **v, t_bool split);
t_bool	process_mode_1(char *arg, t_qmode mode, char ***arr, char **v, int *i);
t_bool	process_mode_2(char *arg, t_qmode mode, char ***arr, char **v, int *i);

char	**process_arg(char *arg, t_bool(*f)(char *, t_qmode, char ***, char **, int *));
void	expand_tree(t_ast *node, int indent);

char    **wildcard_expand_arr(char **in_arr);

#endif
