/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:29:06 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/09 23:30:17 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void _ft_toupper(unsigned int i, char *c)
// {
//   if (i % 2 == 0)
// 		*c -= 32;
// }

// int	main(int ac, char **av)
// {
// 	if (ac == 2){
// 		ft_striteri(av[1], _ft_toupper);
// 		printf("%s\n", av[1]);
// 		ft_striteri(av[2], NULL);
// 		ft_striteri(NULL, _ft_toupper);
// 	}
//   return (0);
// }
