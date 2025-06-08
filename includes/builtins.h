/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:41:47 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 22:18:21 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "typedef.h"

int		exec_env(t_ast *node);
int		exec_export(t_ast *node);
int		exec_unset(t_ast *node);
int		exec_pwd(void);
int		exec_cd(t_ast *node);
int		exec_echo(t_ast *node);
int		exec_exit(t_ast *node);

t_bool	is_builtins(t_ast *node);
int		exec_builtins(t_ast *node);

#endif
