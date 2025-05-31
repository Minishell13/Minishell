/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:33:43 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 16:25:28 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handlemaxcase(int sign)
{
	if (sign == 1)
		return (-1);
	return (0);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long long	num;
	unsigned long long	max;

	i = 0;
	num = 0;
	sign = 1;
	max = 9223372036854775807;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && ft_isdigit((int)str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		if (num >= max)
			return (handlemaxcase(sign));
		i++;
	}
	return ((int)(num * sign));
}

// int	main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (0);
// 	printf("\natoi() Num: %d\n\n", atoi(av[1]));
// 	printf("ft_atoi() Num: %d\n\n", ft_atoi(av[1]));
// 	return (1);
// }
