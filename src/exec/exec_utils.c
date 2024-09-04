/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:44:40 by thsion            #+#    #+#             */
/*   Updated: 2024/09/04 14:40:25 by agtshiba         ###   ########.fr       */
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
		exit(0); // a check si pb a l'exec
	}
	else if (pid > 0)
	{
		while (waitpid(pid, &status, 0) == -1)
			;
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	
}

void before_run(t_node *node, t_data *data)
{
    // Cette fonction vérifie si la commande est un builtin et agit en conséquence
    if (node->type != REDIR && check_is_builtin(node))
    {
		t_exec_node *exec_node = (t_exec_node *)node;
        run_builtin(exec_node, data);
    }
    else
    {
        fork_before_exec(node, data);
    }
}

// void    before_run(t_node *node, t_data *data)
// {
// 	if (check_is_builtin(node))
// 	else
// 		fork_before_exec(node, data);
// }


void    run(t_node *node, t_data *data)
{
	if (node->type == EXEC)
		run_exec_node(node, data);
    else if (node->type == PIPE)
		run_pipe_node(node, data);
    else if (node->type == REDIR)
        run_redir_node(node, data);
}

void    dup_right(int *fd)
{
    close(fd[1]);
    dup2(fd[0], 0);
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
		// printf("Debug: line is NULL\n");
		return (0);
	}
	if (*line == '\0')
	{
		// printf("Debug: line is empty\n");
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
int 	ft_error(char *msg, int exit_code)
{
	g_status = exit_code;
	printf("minishell: %s\n", msg);
	return (0);	
}