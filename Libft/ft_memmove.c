/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 08:33:33 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/09 22:33:28 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	if (d > s)
	{
		while (i < n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
		return (dst);
	}
	ft_memcpy(dst, src, n);
	return (dst);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main()
// {
//   char src[] = "Hello World";
//  char dst[20];
//   printf("Dst: %s\n", (char *)memmove(src + 3, src, 4));
//   printf("Src: %s\n", src);
//   printf("dst: %s\n", (char *)ft_memmove(src + 3, src, 4));
//   printf("Src: %s\n", src);
// }
