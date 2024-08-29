/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:23:39 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:25:34 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../minishell.h"

static size_t	calculate_size(long number)
{
	size_t	len;

	len = 0;
	if (number < 0)
	{
		number = number * (-1);
		len = 1;
	}
	if (number == 0)
		len = 1;
	else
	{
		while (number != 0)
		{
			len++;
			number = number / 10;
		}
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	size;
	long	nb;
	char	*str;
	int		is_negative;

	size = calculate_size((long) n);
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	nb = (long) n;
	is_negative = 0;
	if (nb < 0)
	{
		nb = nb * (-1);
		str[0] = '-';
		is_negative = 1;
	}
	str[size] = '\0';
	while (size > (size_t) is_negative)
	{
		str[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (str);
}
// char *ft_itoa(int number)
// {
//     size_t totalsize;
//     long nb;
//     char *s;
//     int i;

//     totalsize = calculate_size((long)number);
//     //    i = totalsize - 1;
//     s = (char *)malloc(sizeof(char) * (totalsize + 1));
//     if (s == NULL)
//         return (NULL);
//     nb = (long) number;
//     if (nb < 0)
//     {
//         nb = nb * (-1);
//         s[0] = '-';
//     }
//     s[totalsize] = '\0';
//     while (nb > 0)
//     {
//         s[i] = nb % 10 + 48;
//         nb = nb / 10;
//         i--;
//     }
//     s[totalsize] = '\0'; 
//     return (s);
// }
// int main()
// {
//     int n = -12345;
//     printf("%s", ft_itoa(n));
// }
