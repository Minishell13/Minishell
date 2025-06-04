/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:19:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/04 15:46:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "typedef.h"

void	unset_var(char *key);
char	*get_env(char *key);
void	add_var(char *key, char *value);

char	*extract_key(char *arg, int end);
char	*extract_value(char *arg, int end);

void	export_var(char *k, char *v, t_bool alcd1, t_bool alcd2);
void	setup_env(char **env);

#endif
