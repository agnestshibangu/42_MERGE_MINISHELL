/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:50:56 by thsion            #+#    #+#             */
/*   Updated: 2024/09/05 12:07:11 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*input_fixed(char *new_input, char **input)
{
	new_input = join_char(new_input, **input);
	(*input)++;
	return (new_input);
}

char	*quotes_overload(char **input, char *new_input, t_data *data)
{
	int		count_quotes;
	char	quote_type;

	while (**input && is_quotes(**input))
	{
		count_quotes = 0;
		quote_type = **input;
		while (**input == quote_type)
		{
			(*input)++;
			count_quotes++;
		}
		if (wtfami(count_quotes))
		{
			while (**input != quote_type)
			{
				if (**input == '$' && quote_type == '"')
					new_input = convert_money(new_input, input, data);
				if (**input != quote_type)
					new_input = input_fixed(new_input, input);
			}
			(*input)++;
		}
	}
	return (new_input);
}

char	*new_arg(char *new_input, bool *open_tok, char quote)
{
	new_input = join_char(new_input, quote);
	*open_tok = !*open_tok;
	return (new_input);
}

char	*clean(char *new_input, char *input, t_data *data)
{
	bool	open_tok;
	char	quote;

	open_tok = 0;
	quote = 0;
	skip_space(&input);
	while (*input)
	{
		if (is_quoted_arg(input, &quote) && !open_tok)
			new_input = new_arg(new_input, &open_tok, quote);
		if (is_quotes(*input))
			new_input = quotes_overload(&input, new_input, data);
		if (*input && !is_quotes(*input))
		{
			if (open_tok == 1 && (is_space(*input) || is_symbol(*input)))
				new_input = new_arg(new_input, &open_tok, quote);
			if (*input == '$')
				new_input = convert_money(new_input, &input, data);
			else
				new_input = input_fixed(new_input, &input);
		}
	}
	if (open_tok == 1)
		new_input = new_arg(new_input, &open_tok, quote);
	return (new_input);
}

char	*check_fix_input(char *input, t_data *data)
{
	char	*new;

	if (open_quotes(input) || empty_pipe(input))
	{
		free(input);
		return (NULL);
	}
	new = ft_strdup("");
	if (!new)
		return (NULL);
	data->start_input = clean(new, input, data);
	return (data->start_input);
}
