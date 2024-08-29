/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:11:47 by thsion            #+#    #+#             */
/*   Updated: 2024/08/28 17:46:20 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     free_minishell(t_data *data)
{   
    int	nbr_of_lines;
    int i;
	
	nbr_of_lines = 0;
	if (data == NULL)
		return (1);
	if (data->env_vars != NULL)
	{
        while (data->env_vars[nbr_of_lines])
            nbr_of_lines++;
        i = 0;
		while (i < nbr_of_lines)
		{
			free(data->env_vars[i]);
			data->env_vars[i] = NULL;
			i++;
		}
		free(data->env_vars);
	}
    printf("everything has been freed !\n");
    return (0);
}