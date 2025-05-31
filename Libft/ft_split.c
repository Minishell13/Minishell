/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:55:11 by abnsila           #+#    #+#             */
/*   Updated: 2024/12/22 10:36:18 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freearray(char **arr, size_t count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
	return (NULL);
}

int	ft_wordscount(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**ft_splitwords(char **arr, const char *s, char c)
{
	size_t		current;
	size_t		start;
	size_t		count;

	current = 0;
	count = 0;
	while (s[current])
	{
		while (s[current] == c)
			current++;
		if (s[current] == '\0')
			break ;
		start = current;
		while (s[current] && s[current] != c)
			current++;
		arr[count] = ft_substr(s, start, current - start);
		if (arr[count] == NULL)
			return (ft_freearray(arr, count));
		count++;
	}
	arr[count] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words_count;

	if (!s)
		return (NULL);
	words_count = ft_wordscount(s, c);
	arr = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (ft_splitwords(arr, s, c));
}

// #include <stdio.h>

// void	printarr(char	**arr)
// {
// 	int	i;

// 	i = 0;
// 	printf("[");
// 	if (arr)
// 	{
// 		while (arr[i])
// 		{
// 			printf("\"%s\", ", arr[i]);
// 			i++;
// 		}
// 	}
// 	printf("NULL]\n");
// }

// int	main(int ac, char **av)
// {
// 	if (ac != 3)
// 		return (0);
// 	printarr(ft_split(av[1], av[2][0]));
// 	printarr(ft_split(NULL, av[2][0]));
// }
