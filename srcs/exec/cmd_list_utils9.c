/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 17:48:11 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* These functions are for environment variable expansion processing */

bool		ft_check_buffer_size(char **expanded, int *pos, int *buffer_size);
bool		ft_process_char_in_loop(t_minishell *minishell, char *str,
				char **expanded, int *pos);

static bool	ft_process_expansion_iter(t_minishell *minishell, char *str,
		char **expanded, int *pos)
{
	int	*buffer_size;

	buffer_size = &pos[2];
	if (!ft_check_buffer_size(expanded, pos, buffer_size))
		return (false);
	if (!ft_process_char_in_loop(minishell, str, expanded, pos))
		return (false);
	return (true);
}

bool	ft_process_expansion_loop(t_minishell *minishell, char *str,
		char **expanded, int *pos)
{
	int	i;

	i = pos[0];
	while (str[i])
	{
		if (!ft_process_expansion_iter(minishell, str, expanded, pos))
			return (false);
		i = pos[0];
	}
	(*expanded)[pos[1]] = '\0';
	return (true);
}
