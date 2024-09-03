/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:44:44 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/03 17:32:35 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void run_path(char **argv, char **path)
{
    if (access(argv[0], F_OK | X_OK) == 0)
        *path = argv[0];  // If the command is a valid path, use it directly 
    else 
        my_free_tab(argv);
}

void run_command(char **path, char **argv, t_data *data)
{
    *path = get_every_path(data->env_vars, argv[0]);
    if (!*path) 
        my_free_tab(argv);
}

void	run_exec(t_exec_node *exec_node, t_data *data)
{
	char	*path;
	char	**argv;

    path = NULL;
    argv = exec_node->args;
    if (!argv || !argv[0])
        exit(EXIT_FAILURE);
    if (strchr(argv[0], '/') != NULL)  
        run_path(argv, &path);
    else
        run_command(&path, argv, data);
    if (execve(path, argv, data->env_vars) == -1) {
        perror("execve failed");
        if (path != argv[0]) {
            free(path); 
        }
        my_free_tab(argv);
    }
}

int check_is_builtin(t_exec_node *exec_node) 
{
    size_t num_builtins;
    size_t i;
    
    const char *builtins[] = {
        "exit", "echo", "env", "pwd", "export", "unset", "shlvl"
    };
    num_builtins = sizeof(builtins) / sizeof(builtins[0]);
    i = 0;
    while (i < num_builtins)
    {
        if (strcmp(exec_node->args[0], builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

void run_exec_node(t_node *node, t_data *data)
{
    t_exec_node *exec_node = (t_exec_node *)node;

    if (check_is_builtin(exec_node))
    {
        run_builtin(exec_node, data);
    }
    else
    {
        run_exec(exec_node, data);
    }
}


