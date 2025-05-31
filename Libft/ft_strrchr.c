/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:34:27 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/10 00:30:09 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr( const char *str, int c)
{
	unsigned char	search_str;
	int				len;

	search_str = c;
	len = ft_strlen((char *)str);
	while (len >= 0)
	{
		if (str[len] == search_str)
			return ((char *)(&str[len]));
		len--;
	}
	return (NULL);
}

// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	char	*res = ft_strrchr(av[1], av[2][0]);
// 	printf("Res found in: %s", res);
// }
