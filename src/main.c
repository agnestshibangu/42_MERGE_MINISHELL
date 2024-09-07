/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:11:36 by thsion            #+#    #+#             */
/*   Updated: 2024/09/07 20:08:07 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status;

void	show_prompt(t_data *data)
{
	char	*input;
	t_node	*final_node;

	while (1)
	{
		signal_handler();
		input = readline("minishell$ ");
		if (input == NULL || input[0] == '\0')
			;
		if (check_empty_input(input, data))
		{
			add_history(input);
			final_node = starting_tree(input, data);
			data->first_node = final_node;
			if (!final_node)
				free_nodes(final_node);
			else
			{
				before_run(final_node, data);
				free_nodes(final_node);
				free(data->start_input);
			}
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		printf("🚫 Minishell doesn't take arguments 🚫");
	init_env_tab(&data, envp);
	if (!data.env_vars)
		return (1);
	show_prompt(&data);
	return (0);
}
