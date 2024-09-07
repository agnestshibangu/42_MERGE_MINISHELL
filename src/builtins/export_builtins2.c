/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:00:12 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 19:37:01 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_swap(char **tab, char *temp, int a, int b)
{
	temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}

char	**sort_alpha_export(char **tab)
{
	int		a;
	int		b;
	char	*temp;

	a = 0;
	b = 0;
	temp = NULL;
	while (tab[a])
	{
		b = a + 1;
		while (tab[b])
		{
			if (ft_strncmp(tab[a], tab[b], 100) > 0)
				my_swap(tab, temp, a, b);
			b++;
		}
		a++;
	}
	return (tab);
}

void	inside_while(char *searched, char **args, t_data *data, char *name)
{
	int		j;
	int		line;
	int		y;

	searched = ft_strdup(*args);
	j = 0;
	while (searched[j] != '=' && searched[j])
		j++;
	if (searched[j] == '=')
		searched[j] = '\0';
	line = search_for_value(data, searched);
	if (line != -1)
	{
		free(data->env_vars[line]);
		data->env_vars[line] = ft_strdup(*args);
	}
	else
	{
		y = 0;
		name = each_arg_export(args);
		while (data->env_vars[y] != NULL)
			y++;
		create_env(name, data, y);
	}
}

int	ft_export(char **args, t_data *data)
{
	int		i;
	char	*name;
	char	*searched;

	name = NULL;
	searched = NULL;
	i = 1;
	if (!args[1])
		print_export(data);
	while (args[i])
	{
		inside_while(searched, &args[i], data, name);
		i++;
	}
	free(searched);
	return (1);
}
