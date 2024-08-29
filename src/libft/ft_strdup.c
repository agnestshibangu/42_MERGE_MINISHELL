/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:29 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:26:18 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		length;
	char	*strcpy;

	length = 0;
	while (s1[length])
		length++;
	strcpy = malloc(length + 1);
	if (strcpy != NULL)
	{
		i = 0;
		while (s1[i])
		{
			strcpy[i] = s1[i];
			i++;
		}
		strcpy[i] = '\0';
	}
	return (strcpy);
}

// #include <stdio.h>
// int main()
// {
//     const char *str = "coucou";
//     printf("%s", ft_strdup(str));
// }
