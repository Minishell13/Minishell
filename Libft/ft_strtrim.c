/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:07:41 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/10 15:24:26 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start_index;
	size_t	end_index;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start_index = 0;
	while (s1[start_index] && ft_strchr(set, s1[start_index]))
		start_index++;
	end_index = ft_strlen(s1);
	while (end_index >= start_index && ft_strchr(set, s1[end_index - 1]))
		end_index--;
	len = end_index - start_index;
	ptr = ft_substr(s1, start_index, len);
	if (!ptr)
		return (NULL);
	return (ptr);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	printf("Result: %s\n", ft_strtrim(av[1], av[2]));
// 	printf("Result: %zu\n", ft_strlen(ft_strtrim(av[1], av[2])));
// 	printf("Result: %lu\n\n", sizeof(ft_strtrim(av[1], av[2])));
// }
