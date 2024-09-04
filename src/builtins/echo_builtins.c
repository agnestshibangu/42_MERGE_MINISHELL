/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:22 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/04 17:23:21 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **args, int out)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], out);
		if (args[i + 1])
			ft_putchar_fd(' ', out);
		i++;
	}
	ft_putstr_fd("\n", out);
}
