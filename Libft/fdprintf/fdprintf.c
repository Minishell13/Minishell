/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:00:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 15:18:12 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_putstr_fd(char *s, int fd)
{
	if (!s)
		return (fd_putstr_fd("(null)", fd));
	return (write(fd, s, ft_strlen(s)));
}

int	fd_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	fd_check(char c, va_list lst, int fd)
{
	if (c == 's')
		return (fd_putstr_fd(va_arg(lst, char *), fd));
	else if (c == 'd' || c == 'i')
		return (fd_putnbr_fd(va_arg(lst, int), fd));
	else if (c == 'x')
		return (fd_address_fd(va_arg(lst, unsigned int),
				"0123456789abcdef", fd));
	else if (c == 'X')
		return (fd_address_fd(va_arg(lst, unsigned int),
				"0123456789ABCDEF", fd));
	else if (c == 'c')
		return (fd_putchar_fd(va_arg(lst, int), fd));
	else if (c == 'u')
		return (fd_unsign_fd(va_arg(lst, unsigned int), fd));
	else if (c == 'p')
		return (fd_putstr_fd("0x", fd) + fd_address_fd(va_arg(lst,
					unsigned long long), "0123456789abcdef", fd));
	else if (c == '%')
		return (fd_putchar_fd('%', fd));
	else
		return (-1);
}

int	fdprintf(int fd, const char *str, ...)
{
	va_list	lst;

	int (result), (j), (i), (start);
	result = 0;
	i = 0;
	start = 0;
	va_start(lst, str);
	while (str && str[i])
	{
		if (str[i] == '%')
		{
			if (start < i && write(fd, str + start, i - start))
				result += i - start;
			j = fd_check(str[++i], lst, fd);
			result += j;
			start = i + 1;
		}
		else if (i == 0 || str[i - 1] == '%')
			start = i;
		i++;
	}
	if (start < i && write(fd, str + start, i - start))
		result += i - start;
	va_end(lst);
	return (result);
}
