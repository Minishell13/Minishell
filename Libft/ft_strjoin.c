/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/01 12:40:48 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*ptr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	total_size = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ptr = (char *) malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, total_size);
	ft_strlcat(ptr, s2, total_size);
	return (ptr);
}

char	*ft_conststrjoin(char *s1, char *s2)
{
	size_t	lens[2];
	char	*ptr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	lens[0] = ft_strlen(s1);
	lens[1] = ft_strlen(s2);
	ptr = ft_realloc(s1, lens[0] + 1, lens[0] + lens[1] + 1);
	if (!ptr)
	{
		free(s2);
		return NULL;
	}
	ft_memcpy(ptr + lens[0], s2, lens[1]);
	ptr[lens[0] + lens[1]] = '\0';
	free(s2);
	return (ptr);
}



char	*ft_charjoin(char *s, char c)
{
	size_t	len;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	ptr = (char *) ft_realloc(s, len + 1, len + 2);
	if (!ptr) return NULL;
	ptr[len]     = c;
	ptr[len + 1] = '\0';
	return (ptr);
}
