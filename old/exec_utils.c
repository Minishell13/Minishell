/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 07:01:43 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 07:02:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_pwd(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 1 && *arg == '-')
		return (true);
	if (len == 2 && *arg == '-' && *(arg + 1) == '-')
		return (true);
	else if (len > 1 && *arg == '-')
		return (false);
	return (true);
}