/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:16 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:26:10 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../minishell.h"
#include <string.h>

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	fill_tab(char *new, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}

static void	set_mem(char **tab, char const *s, char c)
{
	size_t	count;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] && s[index + count] != c)
			count++;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return ;
			fill_tab(tab[i], (s + index), c);
			i++;
			index = index + count;
		}
		else
			index++;
	}
	tab[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**tab;

	words = count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem(tab, s, c);
	return (tab);
}
// char *extract_word(int start, int end, char const *s)
// {
//     int len = end - start + 1;
//     char *substring = (char *)malloc(len + 1);
//     if (substring == NULL)
//         return (NULL);
//     strncpy(substring, s + start, len);
//     substring[len] = '\0';
//     return substring;
// }
// int countwords(const char *s, char c)
// {
//     int i;
//     int  countwords;
//     i = 0;
//     countwords = 0;
//     while (s[i])
//     {   
//         if (s[i] == c)
//             countwords++;
//         i++;
//     }
//     // add 1 for the last word
//     return (countwords);
// }
// char **ft_split(char const *s, char c)
// {
//     int i = 0;
//     int start = 0;
//     int num_elements;
//     int y = 0;
//     char **result;
//     if (s == NULL || !c)
//         return (NULL);
//     num_elements = countwords(s, c);
//     result = (char **)malloc(num_elements * sizeof(char *));
//     while (s[i])
//     {
//         if (s[i] == c)
//         {
//             // int end = i - 1;
//             result[y] = extract_word(start, i - 1, s);
//             y++;
//             start = i + 1;
//         }
//         i++;
//     }
//     if (start < i)
//         result[y] = extract_word(start, i - 1, s);
//     return (result);
// }
// int main()
// {   
//     char str[] = "coucou les gens c'est moi";
//     char delimiter = ' ';
//     char **result = ft_split(str, delimiter);
//     int num_elements;
//     num_elements = countwords(str, delimiter) + 1;
//     for (int i = 0; i < num_elements; i++)
//         printf("%s\n", result[i]);
//     for (int i = 0; i < num_elements; i++)
//         free (result[i]);
//     return 0;
// }
