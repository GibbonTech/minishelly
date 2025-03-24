/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:58:02 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 19:58:03 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_quoted_word(char const *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i])
		(*i)++;
}

void	ft_skip_normal_word(char const *s, char c, int *i)
{
	while (s[*i] && s[*i] != c && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
}
