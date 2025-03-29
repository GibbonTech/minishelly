/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:00:25 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_quotes(char *str, char *expanded, int *i, int *j)
{
	static char	quote_state = 0;

	if (!quote_state && (str[*i] == '\'' || str[*i] == '\"'))
	{
		quote_state = str[*i];
		expanded[(*j)++] = str[*i];
	}
	else if (quote_state && str[*i] == quote_state)
	{
		quote_state = 0;
		expanded[(*j)++] = str[*i];
	}
	else
		expanded[(*j)++] = str[*i];
	(*i)++;
	return (quote_state);
}

static int	ft_prepare_dollar_expansion(char **expanded, char *var_value,
		int j)
{
	int	needed_size;
	int	var_len;

	var_len = ft_strlen(var_value);
	needed_size = j + var_len + 256;
	if (needed_size <= j || needed_size <= var_len)
		needed_size = j + var_len + 1024;
	if (!ft_resize_if_needed(expanded, j, &needed_size))
	{
		free(var_value);
		return (-1);
	}
	j = ft_copy_var_value(expanded, var_value, j);
	return (j);
}

int	ft_handle_dollar_sign(t_minishell *minishell, char *str, char **expanded,
		int *i)
{
	char	*var_value;
	int		j;

	j = 0;
	if (!*expanded)
	{
		*expanded = ft_calloc(1024, sizeof(char));
		if (!*expanded)
			return (-1);
	}
	while ((*expanded)[j])
		j++;
	(*i)++;
	var_value = ft_expand_env_var_value(minishell, str, i);
	if (!var_value)
		return (-1);
	j = ft_prepare_dollar_expansion(expanded, var_value, j);
	return (j);
}
