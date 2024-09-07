/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:44:40 by thsion            #+#    #+#             */
/*   Updated: 2024/09/07 20:10:13 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("error on fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	fork_before_exec(t_node *node, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = 0;
	pid = ft_fork();
	signal(SIGINT, routine_child);
	if (pid == 0)
	{
		run(node, data);
		exit(0);
	}
	else if (pid > 0)
	{
		while (waitpid(pid, &status, 0) == -1)
			;
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
}

void	before_run(t_node *node, t_data *data)
{
	t_exec_node	*exec_node;

	if (node->type == EXEC && check_is_builtin(node))
	{
		exec_node = (t_exec_node *)node;
		run_builtin(exec_node, data);
	}
	else
	{
		fork_before_exec(node, data);
	}
}

void	run(t_node *node, t_data *data)
{
	if (node->type == EXEC)
		run_exec_node(node, data);
	else if (node->type == PIPE)
		run_pipe_node(node, data);
	else if (node->type == REDIR)
		run_redir_node(node, data);
}

int	search_for_value(t_data *data, char *searched)
{
	int		x;

	x = -1;
	while (data->env_vars[++x])
	{
		if (ft_strncmp(data->env_vars[x], searched, ft_strlen(searched)) == 0)
			return (x);
	}
	return (-1);
}
