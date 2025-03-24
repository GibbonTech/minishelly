/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:15 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 19:17:15 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* External function from cmd_processing_utils3.c */
int	ft_word_len(char *str);

static bool	ft_handle_quote(bool *in_quote, char *quote_type, char current)
{
	if ((current == '\'' || current == '\"') && (!*in_quote
			|| current == *quote_type))
	{
		if (!*in_quote)
		{
			*in_quote = true;
			*quote_type = current;
		}
		else
		{
			*in_quote = false;
			*quote_type = '\0';
		}
		return (true);
	}
	return (false);
}

size_t	ft_count_words(const char *s, char c)
{
	size_t	word_count;
	bool	in_quote;
	char	quote_type;

	word_count = 0;
	in_quote = false;
	quote_type = '\0';
	while (*s && *s == c && !in_quote)
		s++;
	while (*s)
	{
		if (*s != c || in_quote)
		{
			word_count++;
			while (*s && (*s != c || in_quote))
			{
				ft_handle_quote(&in_quote, &quote_type, *s);
				s++;
			}
		}
		while (*s && *s == c && !in_quote)
			s++;
	}
	return (word_count);
}

void	ft_skip_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

void	ft_allocate_word(char **args, char *cmd_cell, int i, int j)
{
	int	word_len;

	word_len = ft_word_len(&cmd_cell[i]);
	args[j] = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!args[j])
	{
		while (--j >= 0)
			free(args[j]);
		free(args);
		return ;
	}
	ft_strlcpy(args[j], &cmd_cell[i], word_len + 1);
}
