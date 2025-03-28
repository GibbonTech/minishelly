/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_substr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:50:09 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:18:15 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_substr(char *str, int start, int len, char *replacement)
{
	char	*result;
	int		repl_len;
	size_t	str_len;

	result = ft_prepare_replace_substr(str, start, len, replacement);
	if (!result)
		return (NULL);
	str_len = ft_strlen(str);
	if (str_len <= (size_t)start)
		return (result);
	ft_copy_prefix(result, str, start);
	repl_len = ft_strlen(replacement);
	ft_copy_replacement(result, replacement, start, repl_len);
	ft_copy_suffix(result, str, start, len);
	free(str);
	return (result);
}
