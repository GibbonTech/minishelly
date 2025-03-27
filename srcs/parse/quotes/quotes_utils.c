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
