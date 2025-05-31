/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:50:09 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/09 21:21:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// #include <stdio.h>

// int	main()
// {
// 	char	arr[10];
// 	int		i;
// 	ft_bzero(arr, sizeof(arr));
// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf("index: %d,  value: %d\n", i, arr[i]);
// 		i++;
// 	}
// 	return (1);
// }
