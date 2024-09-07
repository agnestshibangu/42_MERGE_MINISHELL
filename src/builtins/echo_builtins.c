/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:22 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 11:14:26 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **args, int out)
{
	int	i;
	int	y;
	int	strlen;

	i = -1;
	y = 2;
	strlen = ft_strlen(args[0]);
	if (!strncmp(args[0], "-n", 2))
	{
		if (!args[0][y])
			return ;
		else
		{
			while (args[0][y++] == 'n')
				if (strlen == y)
					return ;
		}
	}
	while (args[++i])
	{
		ft_putstr_fd(args[i], out);
		if (args[i + 1])
			ft_putchar_fd(' ', out);
	}
	ft_putstr_fd("\n", out);
}
