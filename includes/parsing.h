/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:58:45 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 13:16:10 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "typedef.h"

// tree_array
t_ast				*new_tree_node(t_gram gram);
t_ast				*new_tree_leaf(t_gram gram, char *s);
void				tree_add_child(t_ast *parent, t_ast *c);
void				tree_add_sibling(t_ast *node, t_ast *sib);
void				append_to_list(t_list **list, t_list *new_node);

// Parser
t_ast				*parse_command(t_token **tokens);
t_ast				*parse_pipe(t_token **tokens);
t_ast				*parse_compound_command(t_token **tokens);
t_ast				*parse_command_list(t_token **tokens);
t_ast				*parse_complete_command(t_token **tokens);

// Parser2
t_ast				*parse_subshell(t_token **tokens, t_token *after,
						t_token *newpos, char	*bad);
t_ast				*parse_simple_command(t_token **tokens);

// parsing_command
int					count_words(t_list *word_list);
int					fill_words_array(char **arr, t_list *word_list);
t_list				*collect_words(t_token **tokens);
t_bool				fill_args(t_ast *cmd, t_list *words);
t_bool				has_subshell_error(t_token **tokens);

// parsing_command2
void				skip_empty_tokens(t_token **tokens);
int					is_redirect_token(t_token *token);
t_ast				*create_redirect_node(t_token_type type,
						char *file,
						t_ast *list);
int					handle_redirection(t_token **tokens, t_ast *list);
t_ast				*handle_compound_op(t_token **tokens, t_ast *left,
						t_token_type op);

// parsing_command3
int					consume_token_type(t_token **tokens, t_token_type type);
t_bool				check_subshell_errors(t_ast *inner, t_token **tokens,
						t_token **after_paren);
t_bool				is_invalid_start_token(t_token **tokens);
t_bool				has_extra_tokens(t_token **tokens);
t_bool				is_invalid_pipe_token(t_token *token);

// parsing_command4
t_bool 				check_nested_empty(t_token *start, t_token **after);
t_ast				*parse_subshell_redirs(t_token **tokens, t_ast *inner,
						t_ast **redir_list);
t_bool				check_nested_invalid_after_paren(t_token *start,
						t_token **after, char **bad_val);
// Cleanup
// void				free_list(t_list *list);
// void				free_tokens(t_token *token);
// void				free_tree(t_ast *node);
// void				free_all(void);

#endif
