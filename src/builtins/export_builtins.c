/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:32 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 15:44:31 by agtshiba         ###   ########.fr       */
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
	// my_free_tab(data->env_vars);
	data->env_vars = new_env_vars;
	return (1);
}

char	*each_arg_export(char **args)
{
	int		i;
	int		y;
	int		name_len;
	char	*name;

	name = NULL;
	i = 0;
	name_len = ft_strlen(args[0]);
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	if (!name)
	{
		ft_error("minishell : Memory allocation error\n", 1);
		return (NULL);
	}
	y = 0;
	while (args[0][i])
		name[y++] = args[0][i++];
	return (name);
}

int	ft_export(char **args, t_data *data)
{
	int		i;
	int		j;
	int 	y;
	int		line;
	char	*name;
	char	*searched;

	i = 1;
	y = 0;
	while (args[i])
	{
		searched = ft_strdup(args[i]);
		j = 0;
		while (searched[j] != '=' && searched[j])
			j++;
		if (searched[j] == '=')
			searched[j] = '\0';
		line = search_for_value(data, searched);
		free(searched);
		if (line != -1)
		{
			free(data->env_vars[line]);
			data->env_vars[line] = ft_strdup(args[i]);
		}
		else
		{
			y = 0;
			name = each_arg_export(&args[i]);
			while (data->env_vars[y] != NULL)
				y++;
			create_env(name, data, y);
		}
		i++;
	}
	return (1);
}
