/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:17:13 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 15:39:37 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_prepare_export_value(char *value, char **unquoted_value)
{
	*unquoted_value = ft_remove_quotes_from_str(value);
	if (*unquoted_value)
	{
		free(value);
		return (1);
	}
	return (0);
}

static int	ft_handle_export_assignment(t_minishell *minishell, char *arg,
		char *equals)
{
	char	*key;
	char	*value;
	char	*unquoted_value;

	key = ft_substr(arg, 0, equals - arg);
	if (!key)
		return (1);
	if (!ft_is_valid_identifier(key))
	{
		ft_print_invalid_identifier(arg);
		free(key);
		return (1);
	}
	value = ft_strdup(equals + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	unquoted_value = NULL;
	if (ft_prepare_export_value(value, &unquoted_value))
		value = unquoted_value;
	ft_update_env_var(minishell, key, value);
	free(key);
	return (0);
}

static int	ft_handle_export_arg(t_minishell *minishell, char *arg)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		return (ft_handle_export_assignment(minishell, arg, equals));
	}
	else
	{
		if (!ft_is_valid_identifier(arg))
			return (ft_print_invalid_identifier(arg));
	}
	return (0);
}

int	ft_export(t_minishell *minishell, char **args)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		ft_print_export_list(minishell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_handle_export_arg(minishell, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
