/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:22 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 16:34:05 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_there_n(char	**args)
{
	int	y;
	int	strlen;

	y = 2;
	strlen = ft_strlen(args[0]);
	if (!ft_strncmp(args[0], "-n", 2))
	{
		if (!args[0][y])
			return (true);
		else
		{
			while (args[0][y++] == 'n')
				if (strlen == y)
					return (true);
		}
	}
	return (false);
}

void	ft_echo(char **args, int out)
{
	int		i;
	bool	flag;

	i = 0;
	if (is_there_n(args))
	{
		flag = true;
		i++;
	}
	else
		flag = false;
	while (args[i])
	{
		ft_putstr_fd(args[i], out);
		if (args[i + 1])
			ft_putchar_fd(' ', out);
		i++;
	}
	if (flag == false)
		ft_putstr_fd("\n", out);
}
