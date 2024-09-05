/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:59:31 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 12:08:38 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*check_4_pipes(char **start_scan, char *end_input, t_data *data)
{
	t_node	*node;

	node = parse_execution(start_scan, end_input);
	if (!node)
		return (NULL);
	if (peek(start_scan, end_input, "|"))
	{
		getoken(start_scan, end_input, 0, 0);
		if (!check_next_arg(*start_scan, end_input))
		{
			free(node);
			return (NULL);
		}
		node = create_pipe_node(node,
				check_4_pipes(start_scan, end_input, data));
		if (!node)
		{
			free(node);
			return (NULL);
		}
	}
	return (node);
}

int	check_next_arg(char *start_scan, char *end_input)
{
	while (start_scan < end_input && is_space(*start_scan))
		start_scan++;
	if (*start_scan == '|')
	{
		print_error_return("syntax error near unexpected token '||'");
		return (0);
	}
	if (*start_scan == '<' || *start_scan == '>')
	{
		print_error_return("syntax error near unexpected token '|'");
		return (0);
	}
	return (1);
}

t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_pipe_node	*pipe_node;

	pipe_node = malloc(sizeof(*pipe_node));
	if (!pipe_node)
		return (NULL);
	ft_memset(pipe_node, 0, sizeof(*pipe_node));
	pipe_node->type = PIPE;
	pipe_node->left = left;
	pipe_node->right = right;
	if (!pipe_node->right)
	{
		free(pipe_node->left);
		free(pipe_node);
		return (NULL);
	}
	return ((t_node *)pipe_node);
}
