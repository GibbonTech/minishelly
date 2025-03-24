/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:17:13 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 01:19:52 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_env_var(t_minishell *minishell, char *key, char *value)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			free(current->value);
			current->value = value;
			return ;
		}
		current = current->next;
	}
	ft_add_envar(minishell, key, value);
	free(value);
}

bool	ft_is_valid_identifier(char *identifier)
{
	int	i;

	if (!identifier || !*identifier)
		return (false);
	if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
		return (false);
	i = 1;
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_print_invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

void	ft_print_export_list(t_minishell *minishell)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->key, 1);
		if (current->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}
