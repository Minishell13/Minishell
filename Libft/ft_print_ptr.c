/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:27:36 by abnsila           #+#    #+#             */
/*   Updated: 2024/12/07 16:08:19 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(void *p)
{
	if ((void *)p == NULL)
		return (ft_print_str("(nil)"));
	return (ft_print_str("0x")
		+ ft_print_hexa((unsigned long)p, "0123456789abcdef"));
}
