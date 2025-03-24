/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:28:15 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 22:28:17 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordlen_with_quotes(char const *s, char c, int start)
{
	int		i;
	char	quote;

	i = start;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		else
			i++;
	}
	return (i - start);
}

static bool	ft_copy_word(char **dest, char const *s, int start, int len)
{
	int	i;

	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!*dest)
		return (false);
	i = 0;
	while (i < len)
	{
		(*dest)[i] = s[start + i];
		i++;
	}
	(*dest)[i] = '\0';
	return (true);
}

bool	ft_process_word(char **split, char const *s, char c, int pos[2])
{
	int	len;

	while (s[pos[0]] && s[pos[0]] == c)
		pos[0]++;
	if (!s[pos[0]])
		return (true);
	len = ft_wordlen_with_quotes(s, c, pos[0]);
	if (!ft_copy_word(&split[pos[1]], s, pos[0], len))
		return (false);
	pos[0] += len;
	pos[1]++;
	return (true);
}

void	ft_free_split(char **split, int size)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (i < size)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
