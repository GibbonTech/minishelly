/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:29:40 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 13:04:10 by ykhomsi          ###   ########.fr       */
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

static bool	ft_is_special_char(char c, char next)
{
	return (c == ';' || c == '\\' || c == '(' || c == ')'
		|| c == '{' || c == '}' || c == '&' || c == '*'
		|| (c == '|' && next == '|'));
}

static bool	ft_check_unsupported_chars(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else if (!quote && ft_is_special_char(input[i], input[i + 1]))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putchar_fd(input[i], 2);
			ft_putstr_fd("'\n", 2);
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
