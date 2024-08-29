/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:45:27 by thsion            #+#    #+#             */
/*   Updated: 2024/08/29 17:06:01 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int run_builtin(t_exec_node *exec_node, t_data *data)
{
    if (!strncmp(exec_node->args[0], "exit", 4)) {
        ft_exit();
        return 1;
    }
    if (!ft_strncmp(exec_node->args[0], "echo", 4))
    {
        ft_echo(&exec_node->args[1], 1);
        return (1); 
    }
    if (!ft_strncmp(exec_node->args[0], "env", 3) && 
        (exec_node->args[1] == NULL || exec_node->args[1][0] == ' ' || exec_node->args[1][0] == '\0'))
    {
        ft_env(data);
        return (1); 
    }
    if (!ft_strncmp(exec_node->args[0], "pwd", 3) && 
        (exec_node->args[1] == NULL || exec_node->args[1][0] == ' ' || exec_node->args[1][0] == '\0'))
    {
        ft_pwd();
        return (1); 
    }
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
    if (!ft_strncmp(exec_node->args[0], "SHLVL", 5))
    {
        ft_update_shell_level(data);
        return (1);
    }
    return (0);
}

