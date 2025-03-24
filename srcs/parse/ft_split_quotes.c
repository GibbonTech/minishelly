/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:28:23 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 22:28:26 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_quoted_word(const char *s, int *i)
{
	char	quote;
	int		count;

	quote = s[*i];
	(*i)++;
	count = 1;
	while (s[*i] && s[*i] != quote)
	{
		(*i)++;
		count++;
	}
	if (s[*i])
		(*i)++;
	return (count);
}

static int	ft_count_words_local(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			if (s[i] == '"' || s[i] == '\'')
				count += ft_handle_quoted_word(s, &i) - 1;
			else
				while (s[i] && s[i] != c)
					i++;
		}
	}
	return (count);
}

static bool	ft_init_split_local(char const *s, char c, char ***split,
		int *words)
{
	if (!s)
		return (false);
	*words = ft_count_words_local(s, c);
	*split = (char **)malloc(sizeof(char *) * (*words + 1));
	if (!*split)
		return (false);
	return (true);
}

static bool	ft_process_all_words(char **split, char const *s, char c, int words)
{
	int	pos[2];

	pos[0] = 0;
	pos[1] = 0;
	while (pos[1] < words)
	{
		if (!ft_process_word(split, s, c, pos))
		{
			ft_free_split(split, pos[1]);
			return (false);
		}
	}
	return (true);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**split;
	int		words;

	if (!ft_init_split_local(s, c, &split, &words))
		return (NULL);
	if (!ft_process_all_words(split, s, c, words))
		return (NULL);
	split[words] = NULL;
	return (split);
}
