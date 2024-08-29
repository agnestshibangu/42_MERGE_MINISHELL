/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:32 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:35:36 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

// int main()
// {
//     char s1[] = "coucou";
//     char s2[] = "kikou";
//     printf("%s", ft_strjoin(s1, s2));
// }
// char    *mystrcat(char const *s1, char const *s2)
// {
//     char *wholestr;
//     size_t     wholelen;
//     size_t     i;
//     size_t     j;
//     i = 0;
//     j = 0;
//     wholelen = strlen(s1) + strlen(s2);
//     if (wholelen )
//     wholestr = (char *)malloc(wholelen + 1);
//     while (s1[i])
//     {
//         wholestr[i] = s1[i];
//         i++;
//     }
//     while (s2[j])
//     {
//         wholestr[j + i] = s2[j];
//         j++;
//     }
//     wholestr[wholelen] = 0;
//     return (wholestr);
// }
// char    *ft_strjoin(char const *s1, char const *s2)
// {
//     int     totallen;
//     int     i;
//     char    *str;
//     char    *concatstr;
//     i = 0;
//     totallen = strlen(s1) + strlen(s2);
//     concatstr = mystrcat(s1, s2);
//     str = (char *)(malloc(sizeof(char *) * (totallen + 1)));
//     if (!str)
//         return (NULL);
//     while (i < totallen)
//     {
//         str[i] = concatstr[i];
//         i++;
//     }
//     str[totallen] = '\0';
//     free (concatstr);
//     return str;
