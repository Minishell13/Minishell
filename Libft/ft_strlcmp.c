/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:44:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/05 13:45:24 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

t_bool	ft_strlcmp(const char *s1, const char *s2)
{
	size_t	n1;
	size_t	n2;

	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	if ((ft_strncmp(s1, s2, n2) == 0) && n1 == n2)
	{
		return (true);
	}
	return (false);
}
