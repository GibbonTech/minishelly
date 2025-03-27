/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 07:46:56 by ykhomsi          ###   ########.fr       */
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

static int	ft_count_parts(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == c && !ft_in_quotes(str, i))
			count++;
		i++;
	}
	return (count);
}

static void	ft_fill_result(char **result, char *str, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == c && !ft_in_quotes(str, i))
		{
			str[i] = '\0';
			result[j++] = ft_strdup(str + start);
			str[i] = c;
			start = i + 1;
		}
		i++;
	}
	result[j++] = ft_strdup(str + start);
	result[j] = NULL;
}

char	**ft_split_with_quotes(char *str, char c)
{
	char	**result;
	int		count;

	count = ft_count_parts(str, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	ft_fill_result(result, str, c);
	return (result);
}
