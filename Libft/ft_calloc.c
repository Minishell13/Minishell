/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:36:20 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/10 14:33:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	if (size != 0 && count > ((size_t) -1 / size))
		return (NULL);
	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	char	*arr;
// 	int		i;

// 	if (ac != 3)
// 		return (0);
// 	arr = calloc(ft_atoi(av[1]), ft_atoi(av[2]));
// 	if (arr == NULL)
// 		printf("Allocation Fail !");
// 	i = 0;
// 	while (i < (ft_atoi(av[1]) * ft_atoi(av[2])))
// 	{
// 		printf("index: %d,  value: %d\n", i, arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (1);
// }
