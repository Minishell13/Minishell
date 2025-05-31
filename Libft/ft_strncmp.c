/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:11:16 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/10 18:24:09 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s2[i] || s1[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main(int ac, char **av)
// {
// 	printf("str1:%s\nstr2:%s\nretuned:%d\n", av[1], av[2], 
//	strncmp(av[1], av[2], atoi(av[3])));
// 	printf("str1:%s\nstr2:%s\nretuned:%d\n", av[1], av[2], 
//	ft_strncmp(av[1], av[2], atoi(av[3])));
// 	return (1);
// }
