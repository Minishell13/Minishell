/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:56:50 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 10:56:53 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LEXER_H
#ifdef LEXER_H

# include "typedef.h"

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

#endif
