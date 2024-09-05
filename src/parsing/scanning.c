/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:39:14 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 12:10:10 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	getoken(char **start_scan, char *end_scan, char **startoken,
	char **endoken)
{
	char	*str;
	int		type;

	str = *start_scan;
	type = 0;
	while (str < end_scan && is_space(*str))
		str++;
	if (str >= end_scan)
		return (-1);
	if (*str == '"' || *str == '\'')
		type = quoted_token(&str, startoken, endoken);
	else
	{
		if (startoken)
			*startoken = str;
		type = fill_type(&str, type, end_scan);
		if (endoken)
			*endoken = str;
	}
	while (str < end_scan && is_space(*str))
		str++;
	*start_scan = str;
	return (type);
}

int	quoted_token(char **input, char **startoken, char **endoken)
{
	char	quote;

	quote = **input;
	*startoken = *input;
	(*input)++;
	if (**input == quote)
	{
		(*input)++;
		*endoken = *input;
	}
	else
	{
		*startoken = *input;
		while (**input != quote)
			(*input)++;
		*endoken = *input;
		if (is_quotes(**input))
			(*input)++;
	}
	return (EXEC);
}

int	fill_type(char **input, int type, char *end_scan)
{
	if (**input == '|')
	{
		type = PIPE;
		(*input)++;
	}
	else if (**input == '<' || **input == '>')
		type = fill_redirection(input, type);
	else
	{
		type = EXEC;
		while (*input < end_scan && !is_all(**input))
			(*input)++;
	}
	return (type);
}

int	peek(char **start_scan, char *end_input, char *target)
{
	char	*str;

	str = *start_scan;
	while (str < end_input && is_space(*str))
		str++;
	*start_scan = str;
	return (*str && ft_strchr(target, *str));
}
