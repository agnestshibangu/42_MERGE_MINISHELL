/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:57 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:26:58 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <stdio.h>

char	*create_string(char const *s, char *str, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (create_string(s, str, start, len));
}
/* int main()
{   
    char str[] = "coucou";
    int start = 3;
    size_t len = 3;
    printf("%s", ft_substr(str, start, len));
}
*/

// #include <stdio.h>
// #include <stdlib.h>
// char *ft_substr(char const *s, unsigned int start, size_t len);

// int main() 
// {   const char *inputString = "Ceci est un exemple de chaine";
//     unsigned int start = 1; // Index de départ
//     size_t len = 10; // Longueur de la sous-chaîne souhaitée
//     char *result = ft_substr(inputString, start, len);     
//     if (result) {
//         printf("Sous-chaine extraite: %s\n", result);
//         free(result);
//     } else {
//         printf("Erreur lors de l'allocation de mémoire.\n");
//     }
//     return 0;
// }
