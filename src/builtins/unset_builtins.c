/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:39 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/04 17:38:59 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_update_env(char *name, t_data *data)
{
	int	len;
	int	j;
	int	x;

	len = strlen(name);
	j = 0;
	x = 0;
	while (data->env_vars[x] != NULL)
	{
		if (ft_strncmp(data->env_vars[x], name, len) == 0
			&& data->env_vars[x][len] == '=')
		{
			free(data->env_vars[x]);
			j = x;
			while (data->env_vars[j])
			{
				data->env_vars[j] = data->env_vars[j + 1];
				j++;
			}
			data->env_vars[j] = NULL;
		}
		x++;
	}
}

int	ft_unset(char **args, t_data *data)
{
	int		i;
	int		y;
	int		name_len;
	char	*name;

	name = NULL;
	i = 0;
	y = 0;
	name_len = 0;
	name = args[1];
	name_len = ft_strlen(args[1]);
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	if (!name)
	{
		ft_error("Memory allocation error\n", 1);
		return (1);
	}
	while (args[1][i])
		name[y++] = args[1][i++];
	unset_update_env(name, data);
	return (0);
}
