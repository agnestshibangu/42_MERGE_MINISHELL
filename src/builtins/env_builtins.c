/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:25 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/04 17:23:58 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_vars[i])
	{
		ft_putstr_fd(data->env_vars[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (NULL);
}
