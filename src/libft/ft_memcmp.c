/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:24:43 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:25:41 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}
// int main()
// {
//     char str1[] = "Hello, World!";
//     // char str2[] = "Hello, World!";
//     char str3[] = "Hello, Coder!";
//     size_t n = 13; // Number of bytes to compare
//     //Using your memcmp function
//     int result1 = memcmp(str1, str3, n);
//     printf("Result using your memcmp: %d\n", result1);
//     //Using the standard memcmp function for comparison
//     int result2 = memcmp(str1, str3, n);
//     printf("Result using standard memcmp: %d\n", result2);
//     return 0;
// }
