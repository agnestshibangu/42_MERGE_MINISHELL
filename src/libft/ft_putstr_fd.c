/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:25:13 by agtshiba          #+#    #+#             */
/*   Updated: 2024/08/11 13:26:06 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ((void) NULL);
	while (*s)
		write(fd, s++, 1);
}

// int main()
// {
//    	char *message = "hellooooooo";
//   	int fileDescriptor = 1;
//    	ft_putstr_fd(message, fileDescriptor); 
// }
