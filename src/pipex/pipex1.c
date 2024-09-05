/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:22:19 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/05 14:49:21 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec(char *cmd, char **env)
{
	char	*path;
	char	**argv;

	argv = ft_split(cmd, ' ');
	path = get_every_path(env, cmd);
	if (execve(path, argv, env) == -1)
		exit(0);
}

// writing phase, on close R end of pipe, dup file W as EXIT    W == EXIT
void	child(char *cmd, int *p_fd, char **env)
{
	close(p_fd[0]);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	exec(cmd, env);
}

// writing phase, on close W end of pipe, dup file R as ENTRY   R == ENTRY
void	parent(int *p_fd)
{
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
}

int	create_a_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return (0);
	pid = fork();
	if (pid == 0)
		child(cmd, p_fd, env);
	else
		parent(p_fd);
	return (1);
}

int	here_doc(char **av)
{
	char	*ret;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return (1);
	while (1)
	{
		ft_putstr_fd(">", 0);
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0
			&& ret[ft_strlen(av[2])] == '\n')
		{
			free(ret);
			break ;
		}
		write(p_fd[1], ret, ft_strlen(ret));
		free(ret);
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	return (0);
}
