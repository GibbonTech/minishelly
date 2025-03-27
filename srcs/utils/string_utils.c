/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:04:10 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 13:22:54 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_space(input[i]))
			return (false);
		i++;
	}
	return (true);
}
