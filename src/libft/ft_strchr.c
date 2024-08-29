/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:26 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:35:04 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*s != '\0')
	{
		if ((unsigned char)*s == ch)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)*s == ch)
		return ((char *)s);
	return (NULL);
}

// int main()
// {
//     char str[] = "\0";
//     char g = '\0'; // Vous devez utiliser un caractère unique ici
//     char *result = ft_strchr(str, g);
//     if (result)
//         printf("%c\n", g, result - str);
//     else
//         printf("%c\n", g);
//     return 0;
// }
