/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/28 06:11:33 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_in_quotes(char *str, int pos)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (i < pos)
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

bool	ft_update_word_state(char *str, int i, bool *in_quotes,
		bool *in_word)
{
	static char	quote;

	if ((str[i] == '\'' || str[i] == '\"') && !*in_quotes)
	{
		quote = str[i];
		*in_quotes = true;
		*in_word = true;
		return (true);
	}
	else if (str[i] == quote && *in_quotes)
	{
		quote = 0;
		*in_quotes = false;
		return (true);
	}
	return (false);
}

char	**ft_split_with_quotes(char *str, char c)
{
	char	**result;
	int		count;

	if (!str)
		return (NULL);
	count = ft_count_parts_helper(str, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	ft_fill_result_helper(result, str, c);
	return (result);
}
