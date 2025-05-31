/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:04:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 15:19:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDPRINTF_H
# define FDPRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	fd_unsign_fd(unsigned int n, int fd);
int	fd_address_fd(unsigned long long n, char *base, int fd);
int	fd_putnbr_base_fd(unsigned int n, char *base, int fd);
int	fd_putchar_fd(char c, int fd);
int	fd_putstr_fd(char *s, int fd);
int	fd_putnbr_fd(int n, int fd);

int	fd_check(char c, va_list lst, int fd);
int	fdprintf(int fd, const char *str, ...);

#endif
