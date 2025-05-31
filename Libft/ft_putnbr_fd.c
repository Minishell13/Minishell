/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:02:49 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/09 22:59:55 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	else if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(((n % 10) + 48), fd);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>

// int main(int ac, char **av)
// {
// 	int	fd;

// 	if (ac != 3)
// 		return (0);
// 	fd = open("./Test/file.txt", 0x0001);
// 	ft_putnbr_fd(ft_atoi(av[1]), 2);
// 	return (1);
// }
