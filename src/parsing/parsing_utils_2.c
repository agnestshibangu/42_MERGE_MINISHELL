/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:54:54 by thsion            #+#    #+#             */
/*   Updated: 2024/09/03 16:33:53 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	open_quotes(char *input)
{
	int	i;
	int	simple_quote;
	int	double_quotes;

	i = 0;
	simple_quote = 0;
	double_quotes = 0;
	while (input[i])
	{
		quotes_checker(&simple_quote, &double_quotes, input, i);
		i++;
	}
	if (simple_quote || double_quotes)
	{
		print_error_return("open quotes");
		return (true);
	}
	return (false);
}

bool	empty_pipe(char *input)
{
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			while (*input && *input != '|')
			{
				if (!is_space(*input))
					break ;
				input++;
			}
			if (!*input)
			{
				print_error_return("empty pipe");
				return (true);
			}
		}
		input++;
	}
	return (false);
}

void	skip_space(char **input)
{
	while (**input && is_space(**input))
		(*input)++;
}

bool	is_quoted_arg(char *input, char *quote_type)
{
	while (*input && !is_space(*input) && !is_symbol(*input))
	{
		if (is_quotes(*input))
		{
			*quote_type = *input;
			return (true);
		}
		input++;
	}
	return (false);
}

char	*join_char(char *s1, char c)
{
	char	*str;
	int		i;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	str = malloc(sizeof(char) * (len + 2));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}
