/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:11:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 21:31:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

char	**init_arr(void);
int		len_arr(char **arr);
char	**copy_arr(char **new_arr, char **arr);
char	**dup_arr(char **arr);
char	**append_arr(char **arr, char *str);
char	**merge_arr(char **arr1, char **arr2);
char	**inner_merge_arr(char **arr1, char **arr2);
char	**last_item_ptr(char **arr);
void	print_arr(char **arr);
void	clear_arr(char **arr);

#endif
