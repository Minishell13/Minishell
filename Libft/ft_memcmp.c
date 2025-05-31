/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:31:31 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/09 22:16:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((int)(str1[i] - str2[i]));
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int ac, char **av)
// {
// 	if (ac != 4)
// 		return (0);
// 	printf("Diff: %d\n", memcmp(av[1], av[2], atoi(av[3])));
// 	printf("Diff: %d\n", ft_memcmp(av[1], av[2], atoi(av[3])));
// }
