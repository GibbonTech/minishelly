/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_preprocessing_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/26 11:15:42 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_operator(char *input, char *result, int *i, int *j)
{
	if (*i > 0 && input[*i - 1] != ' ' && input[*i - 1] != '<' && input[*i
			- 1] != '>')
		result[(*j)++] = ' ';
	result[(*j)++] = input[(*i)];
	if (input[*i + 1] && ((input[*i] == '>' && input[*i + 1] == '>')
			|| (input[*i] == '<' && input[*i + 1] == '<')))
	{
		result[(*j)++] = input[++(*i)];
		if (input[*i + 1] && input[*i + 1] != ' ')
			result[(*j)++] = ' ';
	}
	else if (input[*i + 1] && input[*i + 1] != ' ' && input[*i + 1] != '>'
		&& input[*i + 1] != '<')
		result[(*j)++] = ' ';
	(*i)++;
}
