/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:29:40 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 22:55:22 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_unclosed_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (true);
		}
		if (input[i])
			i++;
	}
	return (false);
}

static bool	ft_check_unsupported_chars(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' || input[i] == ';' || input[i] == '('
			|| input[i] == ')' || input[i] == '{' || input[i] == '}'
			|| input[i] == '&' || input[i] == '*'
			|| (input[i] == '|' && input[i + 1] == '|'))
		{
			ft_putstr_fd("minishell: syntax error: Not supported: ", 2);
			ft_putstr_fd("\\, ;, (), {}, &, &&, ||, *\n", 2);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_not_handling(char *input)
{
	if (ft_check_unclosed_quotes(input))
		return (true);
	if (ft_check_unsupported_chars(input))
		return (true);
	return (false);
}

bool	ft_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_space(input[i]))
			return (false);
		i++;
	}
	return (true);
}
