/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:25 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 20:06:54 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_env(t_data *data)
{
	int		i;

	i = 0;
	while (data->env_vars[i])
	{
		if (ft_strchr(data->env_vars[i], '='))
			printf("%s\n", data->env_vars[i]);
		i++;
	}
	return (NULL);
}
