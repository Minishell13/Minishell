/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:01:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 15:17:01 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_unsign_fd(unsigned int n, int fd)
{
	int		result;
	char	c;

	result = 0;
	if (n >= 10)
		result += fd_unsign_fd(n / 10, fd);
	c = n % 10 + '0';
	result += fd_putchar_fd(c, fd);
	return (result);
}

int	fd_address_fd(unsigned long long n, char *base, int fd)
{
	int		result;
	char	c;

	result = 0;
	if (n >= 16)
		result += fd_address_fd(n / 16, base, fd);
	c = base[n % 16];
	result += fd_putchar_fd(c, fd);
	return (result);
}

int	fd_putnbr_base_fd(unsigned int n, char *base, int fd)
{
	int		len;
	int		i;
	char	str[100];

	len = 0;
	i = 0;
	while (base[len])
		len++;
	if (n == 0)
		return (fd_putchar_fd('0', fd));
	while (n)
	{
		str[i++] = base[n % len];
		n /= len;
	}
	while (i--)
		fd_putchar_fd(str[i], fd);
	return (i);
}

int	fd_putnbr_fd(int n, int fd)
{
	int		result;
	char	c;

	result = 0;
	if (n < 0)
	{
		result += fd_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		result += fd_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	result += fd_putchar_fd(c, fd);
	return (result);
}
