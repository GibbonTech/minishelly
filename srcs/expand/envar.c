/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:22:15 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:01:55 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_dup_envar_strings(char *key, char *value,
								char **key_dup, char **value_dup)
{
	*key_dup = ft_strdup(key);
	if (!(*key_dup))
		return (false);
	if (value)
	{
		*value_dup = ft_strdup(value);
		if (!(*value_dup))
		{
			free(*key_dup);
			return (false);
		}
	}
	else
		*value_dup = NULL;
	return (true);
}

static t_envar	*ft_create_envar(char *key, char *value)
{
	t_envar	*new_envar;
	char	*key_dup;
	char	*value_dup;

	if (!ft_dup_envar_strings(key, value, &key_dup, &value_dup))
		return (NULL);
	new_envar = malloc(sizeof(t_envar));
	if (!new_envar)
	{
		free(key_dup);
		free(value_dup);
		return (NULL);
	}
	new_envar->key = key_dup;
	new_envar->value = value_dup;
	new_envar->next = NULL;
	return (new_envar);
}

bool	ft_add_envar(t_minishell *minishell, char *key, char *value)
{
	t_envar	*new_envar;
	t_envar	*current;

	new_envar = ft_create_envar(key, value);
	if (!new_envar)
		return (false);
	if (!minishell->env_list)
	{
		minishell->env_list = new_envar;
		return (true);
	}
	current = minishell->env_list;
	while (current->next)
		current = current->next;
	current->next = new_envar;
	return (true);
}
