/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_nbr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:28:23 by abnsila           #+#    #+#             */
/*   Updated: 2024/12/07 16:16:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned_nbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
	{
		len += ft_print_unsigned_nbr(n / 10);
		len += ft_print_char((n % 10) + '0');
	}
	else
		len += ft_print_char(n + '0');
	return (len);
}
