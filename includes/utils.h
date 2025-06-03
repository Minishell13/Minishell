/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:35:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 11:32:23 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "typedef.h"

void	put_error(char *cmd, char *path);
char	*ft_readline();
t_bool	parsing(char *line);
t_bool	execution();
void	launch_shell(char **ev);

#endif
