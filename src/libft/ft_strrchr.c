/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:51 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:26:51 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

// int main()
// {
//     char str[] = "coucou";
//     char g = 'u'; // Vous devez utiliser un caractère unique ici
//     char *result = ft_strrchr(str, g);
//     if (result)
//         printf(" '%c' %ld .\n", g, result - str);
//     else
//         printf(" '%c.\n", g);
//     return 0;
// }
