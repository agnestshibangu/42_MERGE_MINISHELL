/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:54:19 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/05 14:43:43 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*manage_storage(char *storage, char *buffer)
{
	char	*temp;

	if (!storage)
		storage = ft_strdup("");
	temp = storage;
	storage = ft_strjoin(temp, buffer);
	free(temp);
	temp = NULL;
	return (storage);
}

char	*make_line(int fd, char *buffer, char *storage)
{
	int		read_bytes;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (0);
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		storage = manage_storage(storage, buffer);
		if (!storage)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (read_bytes < 0)
		return (NULL);
	return (storage);
}

void	free_backup(char *backup)
{
	free(backup);
	backup = NULL;
}

char	*my_extract(char *line)
{
	size_t	len;
	size_t	start;
	size_t	substring_len;
	char	*backup;
	char	*newline_pos;

	len = 0;
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos == NULL || *newline_pos == '\0')
		return (NULL);
	while (line[len] != '\0' && line + len != newline_pos)
		len++;
	if (line[len] == '\0')
		return (0);
	start = len + 1;
	substring_len = ft_strlen(line) - len;
	backup = ft_substr(line, start, substring_len);
	if (*backup == '\0')
		free_backup(backup);
	line[len + 1] = '\0';
	return (backup);
}

void	free_storage(char *storage)
{
	if (storage)
	{
		free(storage);
		storage = NULL;
	}
}
