/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:11:42 by thsion            #+#    #+#             */
/*   Updated: 2024/08/30 22:31:24 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_update_shell_level(t_data *data)
{
    int x = 0;
    size_t len;
    char *name = "SHLVL";
    int y;
    int z;
    int num_to_update;
    char *temp;
    
    x = 0;
    len = ft_strlen(name);

    while (data->env_vars[x] != NULL)
    {
        if (ft_strncmp(data->env_vars[x], name, len) == 0 && data->env_vars[x][len] == '=')
        {   
            y = 0;
            while (data->env_vars[x][y] != '=')
                y++;
            z = y;    
            num_to_update = ft_atoi(&data->env_vars[x][z + 1]) + 1;
            temp = ft_strdup(ft_itoa(num_to_update));
            z = z + 1;
            y = 0;
            while (temp[y])
                data->env_vars[x][z++] = temp[y++];
        }
        x++;
    }
    return (0);
}

void	handle_in_out(t_data *data)
{    
	data->stdout_cpy = dup(STDOUT_FILENO);
	data->stdin_cpy = dup(STDIN_FILENO);
}

int init_env_tab(t_data *data, char **envp)
{
    char **copy_of_env;
    int     env_len;

    env_len = 0;
    while (envp[env_len])
        env_len++;
    copy_of_env = malloc((env_len + 1) * sizeof(char *));
    if (!copy_of_env)
        return (1);
    env_len = 0;
    while (envp[env_len])
    {   
        copy_of_env[env_len] = ft_strdup(envp[env_len]);
        env_len++;
    }
    copy_of_env[env_len] = NULL;
    data->env_vars = copy_of_env;
    ft_update_shell_level(data);
    handle_in_out(data);
    printf("copy of env done !\n");
    return (0);
}


