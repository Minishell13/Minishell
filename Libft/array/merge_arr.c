/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:12:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:41:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**merge_arr(char **arr1, char **arr2)
{
	int		len1;
	int		len2;
	char	**tmp;
	int		i;

	if (!arr1 || !arr2)
		return (NULL);
	len1 = len_arr(arr1);
	len2 = len_arr(arr2);
	tmp = ft_realloc(arr1, sizeof(char *) * (len1 + 1),
			sizeof(char *) * (len1 + len2 + 1));
	if (!tmp)
		return (clear_arr(arr1), clear_arr(arr2), NULL);
	i = 0;
	while (i < len2)
	{
		tmp[len1 + i] = arr2[i];
		i++;
	}
	tmp[len1 + len2] = NULL;
	return (free(arr2), tmp);
}
