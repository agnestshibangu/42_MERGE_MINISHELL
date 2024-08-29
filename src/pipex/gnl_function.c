/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:21:18 by agtshiba          #+#    #+#             */
/*   Updated: 2024/05/28 21:22:41 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*line;

	storage = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = make_line(fd, buffer, storage);
	free(buffer);
	if (!line)
	{
		free_storage(storage);
		return (NULL);
	}
	if (ft_strchr(line, '\n') || line != NULL)
		storage = my_extract(line);
	return (line);
}
