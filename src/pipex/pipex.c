/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:22:19 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/03 14:56:22 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../../minishell.h"

//int	exec(char *cmd, char **env)

void	exec(char *cmd, char **env)
{
	char	*path;
	char	**argv;

	argv = ft_split(cmd, ' ');
	path = get_every_path(env, cmd);
	if (execve(path, argv, env) == -1)
	{
		// return (0);
		exit(0);
	}
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

void	my_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	find_path_var(char *name)
{
	char	*needle;
	int		needle_len;

	needle = "PATH=";
	needle_len = ft_strlen(needle);
	if (ft_strncmp(name, needle, needle_len) == 0)
		return (1);
	else
		return (0);
}

char	*find_path_variable_function(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (find_path_var(env[i]))
			return (env[i]);
		i++;
	}
	return (NULL);
}

// char	*get_every_path(char **env, char *cmd)
// {
// 	char	**allpath;
// 	char	*path_part;
// 	char	*exec;
// 	int		i;

// 	allpath = ft_split(find_path_variable_function(env), ':');
// 	i = 0;
// 	while (allpath[i])
// 	{
// 		path_part = ft_strjoin(allpath[i], "/");
// 		exec = ft_strjoin(path_part, cmd);
// 		free(path_part);
// 		if (access(exec, F_OK | X_OK) == 0)
// 		{
// 			printf("%s", exec);
// 			return (exec);
// 		}
// 		free(exec);
// 		i++;
// 	}
// 	my_free_tab(allpath);
// 	return (NULL);
// }


char *get_every_path(char **env, char *cmd)
{
	char **allpath;
	char *path_part;
	char *exec;
	int i;

	allpath = ft_split(find_path_variable_function(env), ':');
	i = 0;
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			my_free_tab(allpath);
			return (exec);
		}
		free(exec);
		i++;
	}
	my_free_tab(allpath);
	return (NULL);
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	finish_pipe(char **av, int ac, char **env)
{
	int		fd_out;

	fd_out = open_file(av[ac - 1], 1);
	dup2(fd_out, 1);
	close(fd_out);
	exec(av[ac - 2], env);
}

//void	no_here_doc(char **av, int i)
void	no_here_doc(char **av)
{
	int	fd_in;

	fd_in = open_file(av[1], 0);
	dup2(fd_in, 0);
	close(fd_in);
	// i = 2;
}


void handle_pipex(char **av, int ac, t_data *data)
{	
	int		i;
	char	*cmd;
	char 	**tab;

	tab = data->env_vars;
	i = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		here_doc(av);
		i = 3;
	}
	else
	{
		i = 2;
		no_here_doc(av);
	}
	while (i < ac - 2)
	{
		cmd = av[i];
		create_a_pipe(cmd, tab);
		i++;
	}
	finish_pipe(av, ac, tab);
}