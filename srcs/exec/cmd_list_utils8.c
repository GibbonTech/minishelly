/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:00:29 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_quote_char(t_exp_data *data, char *str, char **expanded)
{
	if (!data->quote_state)
		data->quote_state = str[data->i];
	else if (data->quote_state == str[data->i])
		data->quote_state = 0;
	(*expanded)[data->j++] = str[data->i++];
	return (true);
}

static bool	ft_handle_dollar_in_loop(t_minishell *minishell, char *str,
		char **expanded, int *pos)
{
	int	j;
	int	i;

	i = pos[0];
	j = pos[1];
	pos[0] = i;
	pos[1] = j;
	j = ft_handle_dollar_sign(minishell, str, expanded, &i);
	if (j == -1)
		return (false);
	pos[0] = i;
	pos[1] = j;
	return (true);
}

bool	ft_process_char_in_loop(t_minishell *minishell, char *str,
		char **expanded, int *pos)
{
	t_exp_data	data;

	data.i = pos[0];
	data.j = pos[1];
	data.quote_state = pos[3];
	if (str[data.i] == '\'' || str[data.i] == '\"')
		ft_handle_quote_char(&data, str, expanded);
	else if (str[data.i] == '$' && data.quote_state != '\'' && str[data.i + 1]
		&& (ft_isalnum(str[data.i + 1]) || str[data.i + 1] == '_'
			|| str[data.i + 1] == '?'))
	{
		pos[3] = data.quote_state;
		if (!ft_handle_dollar_in_loop(minishell, str, expanded, pos))
			return (false);
		data.i = pos[0];
		data.j = pos[1];
	}
	else
		(*expanded)[data.j++] = str[data.i++];
	pos[0] = data.i;
	pos[1] = data.j;
	pos[3] = data.quote_state;
	return (true);
}

bool	ft_check_buffer_size(char **expanded, int *pos, int *buffer_size)
{
	if (pos[1] + 2 >= *buffer_size)
	{
		if (!ft_resize_if_needed(expanded, pos[1], buffer_size))
			return (false);
	}
	return (true);
}
