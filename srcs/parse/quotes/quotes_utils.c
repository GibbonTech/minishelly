/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:29:21 by ykhomsi           #+#    #+#             */
/*   Updated: 2023/03/23 22:29:30 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if a character is a quote
 * @param c Character to check
 * @return 1 if quote, 0 otherwise
 */
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/**
 * Get the quote type for a character
 * @param c Character to check
 * @return QUOTE_SINGLE for single quotes, QUOTE_DOUBLE for double quotes,
 *         QUOTE_NONE otherwise
 */
t_quote_type	get_quote_type(char c)
{
	if (c == '\'')
		return (QUOTE_SINGLE);
	if (c == '\"')
		return (QUOTE_DOUBLE);
	return (QUOTE_NONE);
}
