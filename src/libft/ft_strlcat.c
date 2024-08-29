/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:35 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:26:29 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = dst_len;
	if (size <= dst_len)
		dst_len = size;
	if (dst_len < size - 1 && size > 0)
	{
		while (src[i] && dst_len + i < size - 1)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0;
	}
	return (dst_len + src_len);
}

// int main()
// {
//     char dest[20] = "Hello, ";
//     const char *src = "world!";
//     size_t size = sizeof(dest);
//     size_t result = ft_strlcat(dest, src, size);
//     printf("Concatenated String: %s\n", dest);
//     printf("Total Length: %zu\n", result);
//     return 0;
// }
