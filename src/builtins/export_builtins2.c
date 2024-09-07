/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:00:12 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 18:25:07 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../minishell.h"


void 	my_swap(char **tab, char *temp, int a, int b)
{
	temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}

char 	**sort_alpha_export(char **tab)
{
	int		a;
	int 	b;
	char 	*temp;

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


void print_export(t_data *data)
{
	char **copy_for_print;
	char **sorted_array;
	int i;
	
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