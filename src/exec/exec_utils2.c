/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:34:18 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/05 15:00:35 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_right(int *fd)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	dup_left(int *fd)
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
		ft_error("Debug: line is NULL\n", 1);
		return (0);
	}
	if (*line == '\0')
	{
		ft_error("Debug: line is empty\n", 1);
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

int	ft_error(char *msg, int exit_code)
{
	g_status = exit_code;
	printf("minishell: %s\n", msg);
	return (0);
}
