/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:22:30 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/07 17:21:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	search_str;
	size_t			i;

	str = (unsigned char *)s;
	search_str = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == search_str)
			return ((void *)(&str[i]));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	if (ac != 4)
// 		return (0);
// 	printf("memchr Str: %s\n", (char *)ft_memchr(av[1], 
//	av[2][0], ft_atoi(av[3])));
// }
