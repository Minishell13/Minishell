/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:28:02 by abnsila           #+#    #+#             */
/*   Updated: 2024/12/07 15:23:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_nbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (ft_print_str("-2147483648"));
	else if (n < 0)
	{
		n = -n;
		len += ft_print_char('-');
	}
	if (n > 9)
		len += ft_print_nbr(n / 10);
	len += ft_print_char(((n % 10) + 48));
	return (len);
}
