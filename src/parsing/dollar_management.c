/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:30:23 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 11:25:11 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_status(char *new_input)
{
	char	*str_exit_status;
	int		i;

	i = 0;
	str_exit_status = ft_itoa(g_status);
	while (str_exit_status[i])
	{
		new_input = join_char(new_input, str_exit_status[i]);
		i++;
	}
	free(str_exit_status);
	return (new_input);
}

char	*moneys_name(t_data *data, char **input)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *input;
	data->dollar_len = 0;
	while (*tmp && !is_space(*tmp) && !is_quotes(*tmp)
		&& !is_symbol(*tmp) && *tmp != '$')
	{
		data->dollar_len++;
		tmp++;
	}
	data->dollar_name = malloc(sizeof (char) * data->dollar_len + 1);
	if (!data->dollar_name)
		return (NULL);
	while (i < data->dollar_len)
	{
		data->dollar_name[i] = **input;
		i++;
		(*input)++;
	}
	data->dollar_name[i] = '\0';
	return (data->dollar_name);
}

bool	check_moneys_there(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_vars[i])
	{
		if (ft_strncmp(data->dollar_name, data->env_vars[i],
				data->dollar_len) == 0
			&& data->env_vars[i][data->dollar_len] == '=')
		{
			data->dollar_index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

char	*get_the_money(char *new_input, t_data *data)
{
	int	i;

	i = 0;
	while (data->env_vars[data->dollar_index][i] != '=')
		i++;
	i++;
	while (data->env_vars[data->dollar_index][i])
	{
		new_input = join_char(new_input, data->env_vars[data->dollar_index][i]);
		i++;
	}
	return (new_input);
}

char	*convert_money(char *new_input, char **input, t_data *data)
{
	(*input)++;
	if (**input == '?')
	{
		new_input = get_status(new_input);
		(*input)++;
	}
	else
	{
		moneys_name(data, input);
		if (check_moneys_there(data))
			new_input = get_the_money(new_input, data);
		free(data->dollar_name);
	}
	return (new_input);
}
