/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:45:33 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 14:58:44 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_node_left(t_pipe_node *pipe_node, int *fd, t_data *data)
{
	t_redir_node	*redir_node;

	if (pipe_node->left->type == REDIR)
	{
		redir_node = (t_redir_node *)pipe_node->left;
		if (redir_node->redir_type == HEREDOC)
		{
			dup2(data->stdin_cpy, STDIN_FILENO);
			ft_heredoc(redir_node);
			pipe_node->left = redir_node->cmd;
		}
	}
	dup_left(fd);
	run(pipe_node->left, data);
	exit(g_status);
}

void	run_node_right(t_pipe_node *pipe_node, int *fd, t_data *data)
{
	t_redir_node	*redir_node;

	if (pipe_node->right->type == REDIR)
	{
		redir_node = (t_redir_node *)pipe_node->right;
		if (redir_node->redir_type == HEREDOC)
		{
			dup2(data->stdin_cpy, STDIN_FILENO);
			ft_heredoc(redir_node);
			pipe_node->right = redir_node->cmd;
		}
		else
			dup_right(fd);
	}
	else
		dup_right(fd);
	run(pipe_node->right, data);
	exit(g_status);
}

int	is_there_heredoc(t_node *node)
{
	t_redir_node	*redir_node;

	if (node->type == EXEC)
		return (1);
	else
	{
		redir_node = (t_redir_node *)node;
		while (redir_node->redir_type == HEREDOC)
		{
			if (((t_redir_node *)redir_node->cmd)->type == EXEC)
				return (1);
			redir_node = (t_redir_node *)redir_node->cmd;
		}
		if (redir_node->redir_type == HEREDOC)
			return (0);
	}
	return (1);
}

void	run_pipe_node(t_node *node, t_data *data)
{
	t_pipe_node	*pipe_node;
	pid_t		pid1;
	pid_t		pid2;
	int			fd[2];

	pipe_node = (t_pipe_node *)node;
	if (pipe(fd) == -1)
	{
		g_status = 1;
		printf("error");
		exit(g_status);
	}
	pid1 = ft_fork();
	if (pid1 == 0)
		run_node_left(pipe_node, fd, data);
	pid2 = ft_fork();
	if (pid2 == 0)
		run_node_right(pipe_node, fd, data);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
