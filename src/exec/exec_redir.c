/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:45:18 by thsion            #+#    #+#             */
/*   Updated: 2024/08/30 23:26:42 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void reopen_stdin_stdout(int fd)
// {
//     int tty_fd;
//     if (fd == 0)
//     {
//         tty_fd = open("/dev/tty", O_RDONLY);
//         if (tty_fd < 0)
//         {
//             printf("open stdin failed");
//         }
//         dup2(tty_fd, STDIN_FILENO);
//         close(tty_fd);
//     }
//     else if (fd == 1)
//     {
//         tty_fd = open("/dev/tty", O_WRONLY);
//         if (tty_fd < 0)
//         {
//             printf("open stdout failed");
//         }
//         dup2(tty_fd, STDOUT_FILENO);
//         close(tty_fd);
//     }
// }

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

// int handle_close(int fd)
// {
	
// 	close(fd);
// 	//fd = open(".here_doc", O_RDONLY, 0777);
// 	return (fd);
// }

void	run_heredoc(t_redir_node *redir_node)
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
		{
			printf("minishell: warning: here-document delimited by\
			end-of-file (wanted %s)\n", redir_node->file);
			return ;
		}
		if (is_line_delimiter(line, redir_node))
		{
			//free(line);
			close(file);
			return ;
		}
		else
		{
			ft_putstr_fd(line, file);
			ft_putchar_fd('\n', file);
			//free(line);
		}
			// handle_line(line, file);
	}
}


// void	ft_heredoc(t_redir_node *redir_node)
// {
// 	int	file;

// 	run_heredoc(redir_node);
// 	file = open(".here_doc", O_RDONLY, 0777);
// 	// if (file < 0)
// 	// 	ft_error("heredoc");
// 	if (dup2(file, 1) < 0)
// 	// 	ft_error("dup2");
// 	close(file);
// }



#include <fcntl.h>   // pour open()
#include <unistd.h>  // pour read(), write(), close()
#include <stdio.h>   // pour perror()
#include <stdlib.h>  // pour exit()

void ft_heredoc(t_redir_node *redir_node)
{
    int file;
    int output_file;
    char buffer[1024];
    ssize_t bytes_read;

    // Exécutez la fonction qui gère le here document
    run_heredoc(redir_node);

    // Ouvrez le fichier temporaire `.here_doc` en lecture
    file = open(".here_doc", O_RDONLY);
    if (file < 0)
    {
        perror("open .here_doc");
        exit(EXIT_FAILURE); // ou gérer l'erreur comme vous le souhaitez
    }

    // Ouvrez `file1.txt` en écriture (crée le fichier s'il n'existe pas, et le tronque s'il existe)
    output_file = open("file1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (output_file < 0)
    {
        perror("open file1.txt");
        close(file);
        exit(EXIT_FAILURE); // ou gérer l'erreur comme vous le souhaitez
    }

    // Lire le contenu de `.here_doc` et écrire dans `file1.txt`
    while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0)
    {
        if (write(output_file, buffer, bytes_read) != bytes_read)
        {
            perror("write");
            close(file);
            close(output_file);
            exit(EXIT_FAILURE); // ou gérer l'erreur comme vous le souhaitez
        }
    }

    if (bytes_read < 0)
    {
        perror("read");
    }

    // Fermez les descripteurs de fichiers
    close(file);
    close(output_file);
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
	// run(redir_node->cmd, data);
	// reopen_stdin_stdout(redir_node->fd);
}