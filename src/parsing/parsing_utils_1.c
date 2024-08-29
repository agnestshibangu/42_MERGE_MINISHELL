/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:05:17 by thsion            #+#    #+#             */
/*   Updated: 2024/08/26 11:08:30 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

bool	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

bool	is_all(char c)
{
	if (is_quotes(c) || is_symbol(c) || is_space(c))
		return (true);
	return (false);
}

t_node	*print_error_return(char *error)
{
	printf("Minishell: Error: %s.\n", error);
	return (NULL);
}
