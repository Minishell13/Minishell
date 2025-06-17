/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:56:50 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/17 14:37:15 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LEXER_H
#ifdef LEXER_H

# include "typedef.h"

// lexer
int				is_operator_char(char c);
int				operators(int i, char *line, t_token **head);
int				read_word(int i, char *line, t_token **head);
t_token			*lexer(char *line);

// lexer_command
t_token			*create_token(char *value);
void			token_add_back(t_token **head, t_token *new_token);
t_token_type	get_token_type(char *str);
int				read_quoted_word(int i, char *line);
t_bool			has_unclosed_quotes(char *line);

// lexer_command2
int				handle_quoted_part(int *i, char *line, char quote, char **part);
int				handle_unquoted_part(int *i, char *line, char **part);
int				concat_part(char **word, char *part);

#endif
