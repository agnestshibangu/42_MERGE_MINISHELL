/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:45:18 by thsion            #+#    #+#             */
/*   Updated: 2024/08/28 23:09:31 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	reopen_stdin_stdout(int fd)
{
	if (fd == 0)
	{
		if (open("/dev/tty", O_RDONLY) < 0)
			printf("open stdin failed");
	}
	else if (fd == 1)
	{
		if (open("/dev/tty", O_WRONLY) < 0)
			printf("open stdout failed");
	}
}

int handle_close(int fd)
{
	
	close(fd);
	//fd = open(".here_doc", O_RDONLY, 0777);
	return (fd);
}

void	run_heredoc(t_redir_node *redir_node)
{
	char	*line;
	int		file;

	file = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file < 0)
		printf("error");
	// setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by\
			end-of-file (wanted %s)\n", redir_node->file);
			return ;
		}
		if (is_line_delimiter(line, redir_node))
		{
			//free(line);
			close(file);
			//return ;
		}
		else
		{
			ft_putstr_fd(line, file);
			ft_putchar_fd('\n', file);
			free(line);
		}
			// handle_line(line, file);
	}
}

// int run_heredoc(t_redir_node *redir_node)
// void run_heredoc(t_redir_node *redir_node)
// {
// 	char	*line;
// 	int		file;

// 	file = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	if (file < 0)
// 	{
// 		printf("error can't read file");
// 		return;
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			printf("minishell: warning: here-document delimited by end-of-file (wanted %s)\n", redir_node->file);
// 			break;
// 		}
// 		if (ft_strncmp(line, redir_node->file, ft_strlen(redir_node->file)) == 0 && line[ft_strlen(redir_node->file)] == '\0')
// 		{
// 			//free(line);
// 			close(file);
// 			// break ;
// 			//return handle_close(file);
// 		}
// 		ft_putstr_fd(line, file);
// 		ft_putchar_fd('\n', file);
// 		free(line);
// 	}	
// }
	

void ft_heredoc(t_redir_node *redir_node)
{
	// int file;

	run_heredoc(redir_node);
	// file = run_heredoc(redir_node);
	// if (file < 0)
	// {
	// 	printf("error heredoc");
	// 	return;
	// }
	// // Rediriger l'entrée standard vers le fichier de heredoc
	// if (dup2(file, STDIN_FILENO) < 0)
	// {
	// 	printf("error dup2");
	// 	close(file);
	// 	return;
	// }
	// close(file);
}

void run_redir_node(t_node *node, t_data *data)
{
	t_redir_node *redir_node;

	redir_node = (t_redir_node *)node;
	if (redir_node->redir_type == HEREDOC)
	{
		
		ft_heredoc(redir_node);
	}
	(void)data;
	//run(redir_node->cmd, tabenv);
	//reopen_stdin_stdout(redir_node->fd);
}