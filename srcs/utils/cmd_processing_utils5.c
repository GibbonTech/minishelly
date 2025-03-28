/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing_utils5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:41:45 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/28 18:41:45 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_process_quote(char *str, int *i, char *quote, bool *in_quotes)
{
	if ((str[*i] == '\'' || str[*i] == '\"') && !*in_quotes)
	{
		*quote = str[*i];
		*in_quotes = true;
		return (true);
	}
	else if (str[*i] == *quote && *in_quotes)
	{
		*quote = 0;
		*in_quotes = false;
		return (true);
	}
	return (false);
}

void	ft_fill_result(char **result, char *str, char c)
{
	ft_fill_result_helper(result, str, c);
}
