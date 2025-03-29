/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_substr_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:15:12 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 18:07:09 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prepare_replace_substr(char *str, int start, int len,
		char *replacement)
{
	char	*result;
	int		str_len;
	int		repl_len;

	if (!str || !replacement || start < 0)
		return (NULL);
	str_len = ft_strlen(str);
	repl_len = ft_strlen(replacement);
	if (start >= str_len)
		return (ft_strdup(str));
	if (start + len > str_len)
		len = str_len - start;
	result = malloc(str_len - len + repl_len + 1);
	if (!result)
		return (NULL);
	return (result);
}

void	ft_copy_prefix(char *result, char *str, int start)
{
	int	i;

	i = 0;
	while (i < start)
	{
		result[i] = str[i];
		i++;
	}
}

void	ft_copy_replacement(char *result, char *replacement, int start,
		int repl_len)
{
	int	j;

	j = 0;
	while (j < repl_len)
	{
		result[start + j] = replacement[j];
		j++;
	}
}

void	ft_copy_suffix(char *result, char *str, int start, int len)
{
	int	j;
	int	str_len;
	int	repl_len;

	str_len = ft_strlen(str);
	repl_len = ft_strlen(str);
	j = start + len;
	while (j < str_len)
	{
		result[start + repl_len + j - (start + len)] = str[j];
		j++;
	}
	result[start + repl_len + j - (start + len)] = '\0';
}
