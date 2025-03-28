/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:00:19 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_init_expansion_params(int *pos, int buffer_size)
{
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = buffer_size;
	pos[3] = 0;
	return (true);
}

static char	*ft_process_env_expansion(t_minishell *minishell, char *str,
		int *buffer_size)
{
	char	*expanded;
	int		pos[4];

	ft_init_expansion_params(pos, *buffer_size);
	expanded = ft_calloc(*buffer_size, sizeof(char));
	if (!expanded)
		return (NULL);
	if (!ft_process_expansion_loop(minishell, str, &expanded, pos))
	{
		free(expanded);
		return (NULL);
	}
	return (expanded);
}

char	*ft_expand_env_vars(t_minishell *minishell, char *str)
{
	char	*expanded;
	char	*result;
	int		buffer_size;

	if (!str)
		return (NULL);
	if (ft_check_simple_case(str, &result))
		return (result);
	expanded = ft_init_expansion(str, &buffer_size);
	if (!expanded)
		return (NULL);
	result = ft_process_env_expansion(minishell, str, &buffer_size);
	free(expanded);
	return (result);
}
