/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:45:27 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 12:10:04 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_simple_builtins(t_exec_node *exec_node, t_data *data)
{
	if (!strncmp(exec_node->args[0], "exit", 4))
		return (ft_exit(exec_node->args), 1);
	if (!ft_strncmp(exec_node->args[0], "echo", 4))
		return (ft_echo(&exec_node->args[1], 1), 1);
	if (!ft_strncmp(exec_node->args[0], "env", 3)
		&& (exec_node->args[1] == NULL || exec_node->args[1][0] == ' '
		|| exec_node->args[1][0] == '\0'))
		return (ft_env(data), 1);
	if (!ft_strncmp(exec_node->args[0], "pwd", 3)
		&& (exec_node->args[1] == NULL || exec_node->args[1][0] == ' '
		|| exec_node->args[1][0] == '\0'))
		return (ft_pwd(), 1);
	if (!ft_strncmp(exec_node->args[0], "cd", 2)
		&& (exec_node->args[1] == NULL || exec_node->args[1][0] == ' '
		|| exec_node->args[1][0] == '\0'))
		return (ft_cd(exec_node->args[1]), 1);
	return (0);
}

int	run_env_builtins(t_exec_node *exec_node, t_data *data)
{
	if (!ft_strncmp(exec_node->args[0], "export", 6))
	{
		ft_export(exec_node->args, data);
		return (1);
	}
	if (!ft_strncmp(exec_node->args[0], "unset", 5))
	{
		ft_unset(exec_node->args, data);
		return (1);
	}
	return (0);
}

int	run_builtin(t_exec_node *exec_node, t_data *data)
{
	if (run_simple_builtins(exec_node, data))
		return (1);
	if (run_env_builtins(exec_node, data))
		return (1);
	return (0);
}
