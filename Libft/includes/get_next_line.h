/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:29:38 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/25 16:15:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	_ft_strlen(char	*s);
char	*_ft_strchr(const char *str, int c);
size_t	_ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	_ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*_ft_clean(char **static_var);

char	*ft_append_buff(char **static_var, char *buff, ssize_t rb);
char	*ft_get_line(char **static_var, char *end_line);
char	*ft_handle_end_of_read(char **static_var, char *buff, ssize_t rb);

char	*get_next_line(int fd);

#endif