/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:47:46 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/05 15:04:38 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	find_path_var(char *name)
{
	char	*needle;
	int		needle_len;

	needle = "PATH=";
	needle_len = ft_strlen(needle);
	if (ft_strncmp(name, needle, needle_len) == 0)
		return (1);
	else
		return (0);
}

char	*find_path_variable_function(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (find_path_var(env[i]))
			return (env[i]);
		i++;
	}
	return (NULL);
}
