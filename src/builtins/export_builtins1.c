/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:32 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 19:34:09 by agtshiba         ###   ########.fr       */
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

char	**init_env_tab_export(char **envp)
{
	char	**copy_of_env_export;
	int		env_len;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	copy_of_env_export = malloc((env_len + 1) * sizeof(char *));
	if (!copy_of_env_export)
		return (NULL);
	env_len = 0;
	while (envp[env_len])
	{
		copy_of_env_export[env_len] = ft_strdup(envp[env_len]);
		env_len++;
	}
	copy_of_env_export[env_len] = NULL;
	return (copy_of_env_export);
}

char	**create_export_tab(char **copy_for_print)
{
	char	*temp1;
	char	*temp2;
	int		i;
	int		j;

	i = 0;
	while (copy_for_print[i])
	{
		j = 0;
		while (copy_for_print[i][j] != '=' && copy_for_print[i][j])
			j++;
		if (copy_for_print[i][j] == '=')
		{
			temp1 = ft_strjoin("\"", &copy_for_print[i][j + 1]);
			temp2 = ft_strjoin(temp1, "\"");
			free(temp1);
			copy_for_print[i][j + 1] = '\0';
			temp1 = ft_strjoin(copy_for_print[i], temp2);
			free(temp2);
			free(copy_for_print[i]);
			copy_for_print[i] = temp1;
		}
		i++;
	}
	return (copy_for_print);
}

void	print_export(t_data *data)
{
	char	**copy_for_print;
	char	**sorted_array;
	int		i;

	copy_for_print = init_env_tab_export(data->env_vars);
	copy_for_print = create_export_tab(copy_for_print);
	sorted_array = sort_alpha_export(copy_for_print);
	i = 0;
	while (copy_for_print[i])
	{
		printf("declare -x %s", copy_for_print[i]);
		printf("\n");
		i++;
	}
	my_free_tab(copy_for_print);
}
