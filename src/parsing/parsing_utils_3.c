/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:20:49 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 12:09:33 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quotes_checker(int *simple_quote,
		int *double_quotes, char *input, int i)
{
	if (input[i] == '"')
	{
		if (!*simple_quote && !*double_quotes)
			*double_quotes = 1;
		else
			*double_quotes = 0;
	}
	if (input[i] == '\'')
	{
		if (!*double_quotes && !*simple_quote)
			*simple_quote = 1;
		else
			*simple_quote = 0;
	}
}

bool	wtfami(int count_quotes)
{
	if (count_quotes % 2 != 0)
		return (true);
	return (false);
}
