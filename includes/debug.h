/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:43:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/04 15:48:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "typedef.h"

// Parsing
const char	*get_node_type_name(int type);
void		print_ast(t_ast *node, int indent);
void		print_tokens(t_token *head);

// Execution
void		print_arr(char **arr);
void		ast_print(const t_ast *node, int indent);
char		*gram_name(t_gram g);

// AST Utils
t_ast		*ast_new_node(t_gram type);
int			ast_add_child(t_ast *parent, t_ast *child);
char		**ast_create_args(const char *s);
char		**ast_create_args_2(int count, ...);
void		ast_destroy(t_ast *node);

// Builts in execution functions
void		generate_tmpfile(t_redir *redir);

// AST Examples
t_ast		*ft_get_ast_example(int n);

#endif
