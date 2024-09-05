/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:18 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/05 14:55:22 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(char *str)
{
	int		i;
	char	*path;
	char	cwd[256];

	i = 0;
	while (str[i] != ' ')
		i++;
	i = i + 1;
	if (!str || strcmp(str, "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
			return (ft_error("cd: HOME not set\n", 1), 1);
	}
	else
		path = str;
	if (chdir(path) != 0)
		return (ft_error("minishell : chdir issue\n", 1), 1);
	setenv("OLDPWD", getenv("PWD"), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
		return (ft_error("minishell : cd : error", 1), 1);
	return (0);
}
