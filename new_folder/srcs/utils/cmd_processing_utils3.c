/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:40:15 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 19:12:40 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_quotes_start(bool *in_quotes, char *quote, char current)
{
	if ((current == '\'' || current == '"') && !*in_quotes)
	{
		*quote = current;
		*in_quotes = true;
		return (true);
	}
	return (false);
}

static bool	ft_check_quotes_end(bool *in_quotes, char *quote, char current)
{
	if (current == *quote && *in_quotes)
	{
		*in_quotes = false;
		*quote = 0;
		return (true);
	}
	return (false);
}

int	ft_word_len(char *str)
{
	int		i;
	char	quote;
	bool	in_quotes;

	i = 0;
	quote = 0;
	in_quotes = false;
	while (str[i])
	{
		if (ft_check_quotes_start(&in_quotes, &quote, str[i]))
			i++;
		else if (ft_check_quotes_end(&in_quotes, &quote, str[i]))
			i++;
		else if ((str[i] == ' ' || str[i] == '\t') && !in_quotes)
			break ;
		else
			i++;
	}
	return (i);
}
