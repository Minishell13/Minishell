/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:01:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 11:48:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int ac, char **av, char **ev)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)ev;

// 	//! Test Append an element to an array
// 	printf("len: %d\n", len_arr(av));
// 	char **arr = dup_arr(av);
// 	char *str = ft_strdup("END");
// 	char **new_arr = append_arr(arr, str);
// 	if (!new_arr)
// 	{
// 		clear_arr(arr);
// 		free(str);
// 		return (EXIT_FAILURE);
// 	}
// 	clear_arr(arr);
	
// 	print_arr(new_arr);
// 	clear_arr(new_arr);

	
// 	//! Test Merge two arrays
// 	char **arr1 = dup_arr(av);
// 	char **arr2 = dup_arr(av);
// 	char **new_arr = merge_arr(arr1, arr2);
// 	if (!new_arr)
// 	{
// 		clear_arr(arr1);	
// 		clear_arr(arr2);	
// 		return (EXIT_FAILURE);
// 	}
	
// 	print_arr(new_arr);
// 	clear_arr(new_arr);
	
// 	return (EXIT_SUCCESS);
// }