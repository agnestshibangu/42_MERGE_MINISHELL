/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:43 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:26:39 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../../minishell.h"

int	mylen(char const *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	touppercase(unsigned int index, char c)
{
	if (c >= 'a' && c <= 'z')
	{
		if (index % 2 == 0)
			c -= 32;
	}
	return (c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*result;
	int		i;

	i = 0;
	len = mylen(s);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result [i] = '\0';
	return (result);
}

// int main()
// {
// 	const char *s = "coucou";
// 	char *result = ft_strmapi(s, touppercase);
// 	printf("%s", result);
// 	free(result);
// 	return 0;
// }
