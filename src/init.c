/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:11:42 by thsion            #+#    #+#             */
/*   Updated: 2024/08/29 17:09:01 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    printf("copy of env done !\n");
    return (0);
}
