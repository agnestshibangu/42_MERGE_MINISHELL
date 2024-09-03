/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:56:40 by thsion            #+#    #+#             */
/*   Updated: 2024/09/03 15:18:07 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_empty_input(char *input, t_data *data)
{
	if (!input)
	{
		my_free_tab(data->env_vars);
		//free(data);
		// free(input);
		printf("exit\n");
		exit (1);
	}
	if (*input == '\0')
	{
		free(input);
		return (false);
	}
	return (true);
}

t_node	*starting_tree(char *input, t_data *data)
{
	t_node	*tree;
	char	*end_input;
	char	*tmp;

	tmp = check_fix_input(input, data);                                    // creation copie de l'input
	if (!tmp)
		return (NULL);
	data->start_input = tmp;                      // stockage dans data
	end_input = tmp + ft_strlen(tmp);               // pointeur sur la fin de l'input (utile pour token)
	tree = check_4_pipes(&tmp, end_input, data);     // allez on goooooo
	if (!tree)
	{
		free(input);
		free(data->start_input);                  // gestion erreur si tree vide
		return (NULL);
	}
	tree = put_endline(tree, data);                       // mise en place des '\0' entre chaque commandes
	return (tree);                                  // return dans le main et ca part en exec
}

t_node	*put_endline(t_node *tree, t_data *data)
{
	t_exec_node		*exec_node;
	t_redir_node	*redir_node;
	t_pipe_node		*pipe_node;

	data->nbr_cmd = 0;
	if (tree->type == EXEC)
	{
		exec_node = (t_exec_node *)tree;
		put_endline_exec(data, exec_node);
	}
	if (tree->type == REDIR)
	{
		redir_node = (t_redir_node *)tree;
		put_endline(redir_node->cmd, data);
		*redir_node->end_file = 0;
	}
	if (tree->type == PIPE)
	{
		pipe_node = (t_pipe_node *)tree;
		put_endline(pipe_node->left, data);
		put_endline(pipe_node->right, data);
	}
	return (tree);
}
