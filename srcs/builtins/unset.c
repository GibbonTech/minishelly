/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:26:28 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 01:26:39 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_env_var(t_minishell *minishell, char *key)
{
	t_envar	*current;
	t_envar	*prev;

	current = minishell->env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				minishell->env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_minishell *minishell, char **args)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (!ft_is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			ft_remove_env_var(minishell, args[i]);
		i++;
	}
	return (status);
}
