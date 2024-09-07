/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:11:42 by thsion            #+#    #+#             */
/*   Updated: 2024/09/07 18:26:57 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_update_shell_level(t_data *data)
{
	int		x;

	x = -1;
	while (data->env_vars[++x])
	{
		if (ft_strncmp(data->env_vars[x], "SHLVL", 5)
			== 0 && data->env_vars[x][5] == '=')
			data->env_vars[x][6] = (ft_atoi(&data->env_vars[x][6]) + 1) + '0';
	}
	return (0);
}

void	handle_in_out(t_data *data)
{
	data->stdout_cpy = dup(STDOUT_FILENO);
	data->stdin_cpy = dup(STDIN_FILENO);
}

int	init_env_tab(t_data *data, char **envp)
{
	char	**copy_of_env;
	int		env_len;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	copy_of_env = malloc((env_len + 1) * sizeof(char *));
	if (!copy_of_env)
		return (1);
	env_len = 0;
	while (envp[env_len])
	{
		copy_of_env[env_len] = ft_strdup(envp[env_len]);
		env_len++;
	}
	copy_of_env[env_len] = NULL;
	data->env_vars = copy_of_env;
	ft_update_shell_level(data);
	handle_in_out(data);
	return (0);
}

int	search_row(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->env_vars[i])
	{
		if (ft_strncmp(str, data->env_vars[i], ft_strlen(str)) == 0
			&& (data->env_vars[i][ft_strlen(str) == '='
				|| data->env_vars[i][ft_strlen(str)] == '\0']))
			return (i);
		i++;
	}
	return (-1);
}
