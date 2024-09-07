/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:25 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 19:01:47 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



// char	*ft_env(t_data *data)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	while (data->env_vars[i])
// 	{
// 		j = 0;
// 		while (data->env_vars[i][j])
// 		{
// 			if (data->env_vars[i][j] == '=')
// 			{
// 				ft_putstr_fd(data->env_vars[i], 1);
// 				ft_putchar_fd('\n', 1);
// 				i++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_vars[i])
	{
		if (ft_strchr(data->env_vars[i], '='))
			printf("%s\n", data->env_vars[i]);
		i++;
	}
	return (NULL);
}