/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:05 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:25:58 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}
// #include "libft.h"
// void	ft_putendl_fd(char *s, int fd)
// {
// 	int	i;
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	write(fd, s, i);
// 	write(fd, "\n", 1);
// }
