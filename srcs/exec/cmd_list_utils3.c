/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:00:22 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_alloc_expanded_args(char ***expanded_args, int count)
{
	*expanded_args = malloc(sizeof(char *) * (count + 1));
	if (!*expanded_args)
		return (false);
	return (true);
}

bool	ft_process_expand_args(t_minishell *minishell, char **cmd_args,
		char **expanded_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		expanded_args[i] = ft_expand_env_vars(minishell, cmd_args[i]);
		if (!expanded_args[i])
		{
			while (--i >= 0)
				free(expanded_args[i]);
			free(expanded_args);
			return (false);
		}
		i++;
	}
	expanded_args[i] = NULL;
	return (true);
}

bool	ft_init_cmd_creation(t_minishell *minishell, char **cmd_args,
		t_cmd **new_cmd, char ***expanded_args)
{
	int	i;

	*new_cmd = malloc(sizeof(t_cmd));
	if (!*new_cmd)
		return (false);
	i = 0;
	while (cmd_args[i])
		i++;
	if (!ft_alloc_expanded_args(expanded_args, i))
	{
		free(*new_cmd);
		return (false);
	}
	if (!ft_process_expand_args(minishell, cmd_args, *expanded_args))
	{
		free(*new_cmd);
		return (false);
	}
	return (true);
}
