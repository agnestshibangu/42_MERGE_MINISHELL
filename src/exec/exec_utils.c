/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:44:40 by thsion            #+#    #+#             */
/*   Updated: 2024/08/28 23:27:52 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char 	*isolating_first_argument(char *str)
{
	char *name = NULL;
    int i;
    int y;
    int name_len;

    i = 0;
    y = 0;
    name_len = 0;

    // isolating argument
    while (str[i] != ' ')
        i++;
    i = i + 1;
    
  
    while (str[i + name_len])
        name_len++;

    name = (char *)malloc(sizeof(char) * (name_len + 1));
    if (!name)
        printf("Memory allocation error\n");
    while (str[i])
	{
		name[y++] = str[i++];
	}
	return (name);
}


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

void    run(t_node *node, t_data *data)
{
    // run_exec_node(node, tabenv);
    // EXEC
    if (node->type == EXEC)
        run_exec_node(node, data);
    // PIPE
    else if (node->type == PIPE)
        run_pipe_node(node, data);
    // REDIR
    else if (node->type == REDIR)
        run_redir_node(node, data);
}

void    dup_right(int *fd)
{
    close(fd[1]); // Close the write end of the pipe in the right process
    dup2(fd[0], 0); // Redirect stdin to the read end of the pipe
    close(fd[0]);
}

void   dup_left(int *fd)
{
    close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);    
}

int	is_line_delimiter(char *line, t_redir_node *redir_node)
{
	size_t	line_len;
	size_t	delimiter_len;

	if (!line)
	{
		printf("Debug: line is NULL\n");
		return (0);
	}
	if (*line == '\0')
	{
		printf("Debug: line is empty\n");
		return (0);
	}
	line_len = ft_strlen(line);
	delimiter_len = ft_strlen(redir_node->file);
	if (ft_strncmp(line, redir_node->file, delimiter_len) == 0
		&& (line_len == delimiter_len))
		return (1);
	else
		return (0);
}

void	handle_line(char *line, int file)
{
	ft_putstr_fd(line, file);
	ft_putchar_fd('\n', file);
	free(line);
}