/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:28 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/04 17:24:56 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_input_exit(char *input, t_data *data)
{
	int		i;
	char	**input_cpy;

	i = 0;
	if (!input)
		return (1);
	input_cpy = ft_split(input, ' ');
	if (strcmp(input_cpy[0], "exit") == 0)
	{
		while (input_cpy[i])
			i++;
		if (i > 2)
		{
			ft_error("too many arguments", 1);
			my_free_tab(input_cpy);
			return (g_status = 1, 0);
		}
		else
			ft_exit_and_free(input_cpy, data);
	}
	my_free_tab(input_cpy);
	return (1);
}

void	ft_exit_and_free(char **input_cpy, t_data *data)
{
	int	i;

	printf("free and exit\n");
	if (input_cpy[1])
	{
		i = 0;
		while (input_cpy[1][i])
		{
			if (!ft_isdigit(input_cpy[1][i]))
			{
				printf("minishell: exit: %s: numeric argument required\n",
					input_cpy[1]);
				my_free_tab(input_cpy);
				my_free_tab(data->env_vars);
				exit (1);
			}
			i++;
		}
	}
	my_free_tab(input_cpy);
	my_free_tab(data->env_vars);
	exit(1);
}

void	actualize_status_and_exit(char *status)
{
	g_status = ft_atoi(status);
	if (g_status >= 0 && g_status <= 255)
		exit(g_status);
	else
	{
		g_status %= 256;
		exit(g_status);
	}
}

void	ft_exit(char **args)
{
	int	i;

	if (args[1])
	{
		i = 0;
		while (args[1][i])
		{
			printf("je suis dans la premiere condition");
			if (!ft_isdigit(args[1][i]))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n",
					args[1]);
				exit (1);
			}
			i++;
		}
		actualize_status_and_exit(args[1]);
	}
	else
	{
		printf("je suis dans la seconde condition");
		exit(g_status);
	}
}
