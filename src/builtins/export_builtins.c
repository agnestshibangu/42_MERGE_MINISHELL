/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:32 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/04 17:20:48 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_env(char *name, t_data *data, int i)
{
	char	**new_env_vars;

	new_env_vars = malloc(sizeof(char *) * (i + 2));
	if (!new_env_vars)
	{
		ft_error("minishell : no env vars\n", 1);
		return (1);
	}
	i = 0;
	while (data->env_vars[i])
	{
		new_env_vars[i] = data->env_vars[i];
		i++;
	}
	new_env_vars[i] = strdup(name);
	new_env_vars[i + 1] = NULL;
	data->env_vars = new_env_vars;
	return (1);
}

int	ft_export(char **args, t_data *data)
{
	int		i;
	int		y;
	int		name_len;
	char	*name;

	name = NULL;
	i = 0;
	name_len = 0;
	name_len = ft_strlen(args[1]);
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	if (!name)
	{
		ft_error("minishell : Memory allocation error\n", 1);
		return (1);
	}
	y = 0;
	while (args[1][i])
		name[y++] = args[1][i++];
	while (data->env_vars[i] != NULL)
		i++;
	create_env(name, data, i);
	return (1);
}
