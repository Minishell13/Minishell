/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:35:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 11:28:25 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "typedef.h"

// Parsing Cleanup
void	free_string_array(char **arr);
void	free_tokens(t_token *token);
void	free_list(t_list *list);
void	free_tree(t_ast *node);
void	free_all();

// Execution Cleanup
void	ft_free_array(char **arr);
void	cleanup_loop(char *line);
void	clear_sh(t_ast *root);
void	destroy();

#endif
