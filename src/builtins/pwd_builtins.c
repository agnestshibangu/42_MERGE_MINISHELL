/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:36 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 18:28:44 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_error("minishell : error pwd", 1);
		return (0);
	}
	else
	{
		ft_putstr_fd(cwd, 1);
		printf("\n");
		return (1);
	}
}
