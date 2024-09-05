/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:45:18 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 14:24:17 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reopen_stdin_stdout(int fd)
{
	if (fd == 0)
	{
		if (open("/dev/tty", O_RDONLY) < 0)
			ft_error("minishell : open stdin failed", 1);
	}
	else if (fd == 1)
	{
		if (open("/dev/tty", O_WRONLY) < 0)
			ft_error("minishell : open stdout failed", 1);
	}
}

int	run_heredoc(t_redir_node *redir_node)
{
	char	*line;
	int		file;

	file = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file < 0)
		printf("error");
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (ft_error("minishell: error no line", 1), 0);
		if (is_line_delimiter(line, redir_node))
		{
			close(file);
			return (0);
		}
		else
		{
			ft_putstr_fd(line, file);
			ft_putchar_fd('\n', file);
		}
	}
}

void	ft_heredoc(t_redir_node *redir_node)
{
	int	file;

	file = 0;
	run_heredoc(redir_node);
	file = open(".here_doc", O_RDONLY, 0777);
	if (file < 0)
		ft_error("minishell: error with heredoc", 1);
	if (dup2(file, 0) < 0)
		ft_error("minishell: failed to dup2", 1);
	close(file);
}

void	run_redir_node(t_node *node, t_data *data)
{
	t_redir_node	*redir_node;

	redir_node = (t_redir_node *)node;
	if (redir_node->redir_type == HEREDOC)
	{
		dup2(data->stdin_cpy, STDIN_FILENO);
		ft_heredoc(redir_node);
	}
	else
	{
		close(redir_node->fd);
		open(redir_node->file, redir_node->mode, 0777);
	}
	run(redir_node->cmd, data);
	reopen_stdin_stdout(redir_node->fd);
}
