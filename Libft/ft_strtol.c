/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:26:38 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/17 11:45:13 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
		if (str[(*i)++] == '-')
			sign = -1;
	return (sign);
}

long	process_str(const char *str, int i, int sign, t_bool *overflow)
{
	int					digit;
	unsigned long long	limit;
	unsigned long long	result;

	digit = 0;
	result = 0;
	if (sign == 1)
		limit = LONG_MAX;
	else
		limit = (unsigned long long)LONG_MAX + 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (limit - digit) / 10)
		{
			*overflow = true;
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + digit;
		i++;
	}
	return (sign * (long)result);
}

long	ft_strtol(const char *str, t_bool *overflow)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	if (overflow)
		*overflow = false;
	sign = get_sign(str, &i);
	result = process_str(str, i, sign, overflow);
	return (result);
}
