/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:24:54 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:25:52 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*(ptr++) = (unsigned char)c;
	return (b);
}
// void    *ft_memset(void *b, int c, size_t len)
// {
//     size_t      i;
//     i = 0;
//     if (!b)
//         return (NULL);
//     while(i < len)
//     {
//         *(unsigned char*)(b + i) = (unsigned char)c;
//         i++;
//     }
//     return (b);
// }
