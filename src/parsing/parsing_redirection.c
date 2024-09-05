/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:56:30 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 12:09:08 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*parse_redirection(t_node *node, char **start_scan, char *end_input)
{
	int		token_type;
	char	*start_file;
	char	*end_file;

	while (peek(start_scan, end_input, "<>"))
	{
		token_type = getoken(start_scan, end_input, 0, 0);
		if (getoken(start_scan, end_input, &start_file, &end_file) != EXEC)
		{
			free(node);
			return (print_error_return
				("missing file or delimiter for redirection"));
		}
		node = create_redir_node(token_type, node, start_file, end_file);
	}
	return (node);
}

t_node	*create_redir_node(int token_type, t_node *cmd, char *start_file,
			char *end_file)
{
	t_redir_node	*redir_node;

	redir_node = malloc(sizeof(*redir_node));
	if (!redir_node)
		return (NULL);
	ft_memset(redir_node, 0, sizeof(*redir_node));
	redir_node->type = REDIR;
	redir_node->redir_type = token_type;
	if (token_type == HEREDOC)
		g_status = -42;
	redir_node->cmd = cmd;
	redir_node->file = start_file;
	redir_node->end_file = end_file;
	init_redirection(token_type, redir_node);
	if (cmd->type == REDIR)
		return (multiple_redir(cmd, redir_node));
	return ((t_node *)redir_node);
}

void	init_redirection(int token_type, t_redir_node *redir_node)
{
	if (token_type == APPEND)
	{
		redir_node->mode = O_RDWR | O_CREAT | O_APPEND;
		redir_node->fd = 1;
	}
	if (token_type == OUT_REDIR)
	{
		redir_node->mode = O_RDWR | O_CREAT | O_TRUNC;
		redir_node->fd = 1;
	}
	if (token_type == IN_REDIR)
	{
		redir_node->mode = O_RDONLY;
		redir_node->fd = 0;
	}
}

t_node	*multiple_redir(t_node *cmd, t_redir_node *prev_redir)
{
	t_redir_node	*first_redir;

	first_redir = (t_redir_node *)cmd;
	while (first_redir->cmd->type == REDIR)
		first_redir = (t_redir_node *)first_redir->cmd;
	if (first_redir->cmd->type == EXEC)
	{
		prev_redir->cmd = first_redir->cmd;
		first_redir->cmd = (t_node *)prev_redir;
	}
	return ((t_node *)cmd);
}

int	fill_redirection(char **input, int type)
{
	if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
		{
			type = HEREDOC;
			(*input)++;
		}
		else
			type = IN_REDIR;
	}
	else if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
		{
			type = APPEND;
			(*input)++;
		}
		else
			type = OUT_REDIR;
	}
	return (type);
}
