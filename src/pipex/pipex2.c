/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:45:37 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 14:04:06 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_every_path(char **env, char *cmd)
{
	char	**allpath;
	char	*path_part;
	char	*exec;
	int		i;

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

void	no_here_doc(char **av)
{
	int	fd_in;

	fd_in = open_file(av[1], 0);
	dup2(fd_in, 0);
	close(fd_in);
}

void	handle_pipex(char **av, int ac, t_data *data)
{
	int		i;
	char	*cmd;
	char	**tab;

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
