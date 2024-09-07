/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:21:18 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/07 18:28:04 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* int	ft_cd(char *str)
{
	int		i;
	char	*path;
	char	cwd[256];

	i = 0;
	while (str[i] != ' ')
		i++;
	i = i + 1;
	if (!str || strcmp(str, "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
			return (ft_error("cd: HOME not set\n", 1), 1);
	}
	else
		path = str;
	if (chdir(path) != 0)
		return (ft_error("minishell : chdir issue\n", 1), 1);
	setenv("OLDPWD", getenv("PWD"), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
		return (ft_error("minishell : cd : error", 1), 1);
	return (0);
} */

char	*get_home(t_data *data)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 5;
	path = ft_strdup("");
	while (data->env_vars[i])
	{
		if (ft_strncmp(data->env_vars[i], "HOME=", 5) == 0)
			break ;
		i++;
	}
	if (!data->env_vars[i])
	{
		printf("HOME not set in env");
		return (free(path), NULL);
	}
	path = ft_strjoin(path, &data->env_vars[i][j]);
	return (path);
}

int	switch_dir(char *path)
{
	if (chdir(path) == -1)
	{
		printf("cd : %s : no such file or directory\n", path);
		return (1);
	}
	return (0);
}

int	go_home(t_data *data)
{
	char	*path;

	path = get_home(data);
	if (!path)
	{
		free (path);
		return (1);
	}
	switch_dir(path);
	free(path);
	return (0);
}

void	actu_env(char *dir, char *var, t_data *data)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = ft_strjoin(var, dir);
	i = search_row(data, var);
	free(data->env_vars[i]);
	data->env_vars[i] = NULL;
	data->env_vars[i] = ft_strdup(pwd);
	free(pwd);
}

int	ft_cd(char **args, t_data *data)
{
	char	*old_dir;
	char	*cur_dir;

	old_dir = NULL;
	cur_dir = NULL;
	old_dir = getcwd(old_dir, 0);
	if (args[2])
		return (printf("bash : cd : too many arguments\n"), 1);
	if (!args[1])
	{
		if (go_home(data) == 1)
			return (1);
	}
	else
	{
		if (switch_dir(args[1]) == 1)
			return (free(old_dir), 1);
	}
	cur_dir = getcwd(cur_dir, 0);
	actu_env(old_dir, "OLDPWD=", data);
	actu_env(cur_dir, "PWD=", data);
	free(old_dir);
	free(cur_dir);
	g_status = 0;
	return (0);
}
