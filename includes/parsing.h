/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:58:45 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/31 22:10:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "typedef.h"

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_list
{
	t_token			*token;// Each list node contains a pointer to a t_token
	struct s_list	*next;// Pointer to the next list node
}					t_list;

typedef struct s_arr
{
	int				size;
	int				used;
	int				elem_size;
	void			*arr;
}					t_arr;

typedef struct s_parse_data
{
	t_ast			*cmd;
	t_ast			*rlist;
	t_list			*words;
	t_bool			flag;
}					t_parse_data;

// lexer
int					is_operator_char(char c);
int					operators(int i, char *line, t_token **head);
int					read_word(int i, char *line, t_token **head);
t_token				*lexer(char *line);

// lexer_command
t_token				*create_token(char *value);
void				token_add_back(t_token **head, t_token *new_token);
t_token_type		get_token_type(char *str);
int					read_quoted_word(int i, char *line);
t_bool				has_unclosed_quotes(char *line);

// lexer_command2
int					read_quoted_if_needed(int i, char *line, char *quot);
int					read_operator_if_needed(int i, char *line, t_token **head);
int					read_word_loop(int i, char *line);
int					handle_quotation_end(int i, char quot, char *line);
t_ast				*parse_subshell_redirs(t_token **tokens, t_ast *inner,
						t_ast **redir_list);

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
t_ast				*parse_subshell(t_token **tokens);
t_ast				*parse_redirect_list(t_token **tokens);
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



void 	free_list(t_list *list);
void	free_tokens(t_token *token);
void	free_tree(t_ast *node);
void	free_all(t_token *token, t_ast *ast);

#endif
