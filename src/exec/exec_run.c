/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:44:44 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 20:08:58 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_path(char **argv, char **path)
{
	if (access(argv[0], F_OK | X_OK) == 0)
		*path = argv[0];
	else
		my_free_tab(argv);
}

void	run_command(char **path, char **argv, t_data *data)
{
	*path = get_every_path(data->env_vars, argv[0]);
	if (!*path)
	{
		ft_error("command not found", -1);
		free(argv[0]);
		exit(1);
	}
}

void	run_exec(t_exec_node *exec_node, t_data *data)
{
	char	*path;
	char	**argv;

	path = NULL;
	argv = exec_node->args;
	if (!argv || !argv[0])
		exit(EXIT_FAILURE);
	if (ft_strchr(argv[0], '/') != NULL)
		run_path(argv, &path);
	else
		run_command(&path, argv, data);
	if (execve(path, argv, data->env_vars) == -1)
	{
		ft_error("commmand not found", -1);
		free(argv[0]);
	}
}

int	check_is_builtin(t_node *node)
{
	t_exec_node	*exec_node;

	exec_node = (t_exec_node *)node;
	if (!strncmp(exec_node->args[0], "exit", 4))
		return (1);
	if (!ft_strncmp(exec_node->args[0], "echo", 4))
		return (1);
	if (!ft_strncmp(exec_node->args[0], "env", 3)
		&& (exec_node->args[1] == NULL || exec_node->args[1][0] == ' '
		|| exec_node->args[1][0] == '\0'))
		return (1);
	if (!ft_strncmp(exec_node->args[0], "pwd", 3)
		&& (exec_node->args[1] == NULL || exec_node->args[1][0] == ' '
		|| exec_node->args[1][0] == '\0'))
		return (1);
	if (!ft_strncmp(exec_node->args[0], "export", 6))
		return (1);
	if (!ft_strncmp(exec_node->args[0], "unset", 5))
		return (1);
	if (!ft_strncmp(exec_node->args[0], "cd", 2))
		return (1);
	return (0);
}

void	run_exec_node(t_node *node, t_data *data)
{
	t_exec_node	*exec_node;

	exec_node = (t_exec_node *)node;
	if (check_is_builtin(node))
		run_builtin(exec_node, data);
	else
		run_exec(exec_node, data);
}
