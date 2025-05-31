/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:46:02 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/10 14:36:22 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// int	main()
// {
// 	char  str1[] = "Hello World";
// 	char  str2[] = "Hello World";
// 	memset(str1 + 2, 36131, 2);
// 	printf("Str1: %s\n", str1);
// 	ft_memset(str2 + 2, 36131, 2);
// 	printf("Str2: %s\n", str2);
// 	return (1);
// }

// int	main()
// {
// 	char  str[] = "Hello World";
// 	int arr[2] = {777, 42};
// 	char  *p1 = (char *)&arr[0];
// 	char  *p2 = (char *)&arr[1];
// 	ft_memset(str + 4, 0b00100011, 1);
// 	ft_memset(p1, 57, 1);
// 	ft_memset(p1 + 1, 5, 1);
// 	ft_memset(p2, 0b11000111, 1);
	// ft_memset(p2 + 1, 0b11111010, 1);
// 	ft_memset(p2 + 2, 255, 1);
// 	ft_memset(p2 + 3, 255, 1);
// 	return (1);
// }

// int main() {
//     int     *arr;
//     size_t  i;
//     size_t  j;
//     arr = (int *)malloc(10 * sizeof(int));
//     if (!arr) {
//         perror("malloc failed");
//         return 1;
//     }
//     j = 0;
//     while (j < 10)
//     {
//         char  *p = (char *)&arr[j];
//         memset(p + 0, 0b00111001, 1); // Set the first byte
//         memset(p + 1, 0b00000101, 1); // Set the second byte
//         memset(p + 2, 0b00000000, 1); // Set the third byte
//         memset(p + 3, 0b00000000, 1); // Set the fourth byte
//         j++;
//     }
//     for (i = 0; i < 10; i++) {
//         printf("arr[%zu] = %d\n", i, arr[i]);
//     }
//     free(arr);
//     return 0;
// }
