/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:43:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 11:15:17 by abnsila          ###   ########.fr       */
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
void		ast_print(const t_ast *node, int indent);
char		*gram_name(t_gram g);

#endif
