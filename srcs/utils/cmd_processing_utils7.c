/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing_utils7.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:41:35 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/28 23:51:52 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_fill_result(t_result_state *state)
{
	state->i = 0;
	state->j = 0;
	state->start = 0;
	state->quote = 0;
	state->in_quotes = false;
}

static void	ft_process_fill_result_char(t_result_state *state, char *str,
		char c, char **result)
{
	if (ft_process_quote(str, &state->i, &state->quote, &state->in_quotes))
	{
		state->i++;
		return ;
	}
	if (str[state->i] == c && !state->in_quotes)
	{
		if (state->i > state->start)
			result[state->j++] = ft_substr(str, state->start, state->i
					- state->start);
		while (str[state->i] && str[state->i] == c)
			state->i++;
		state->start = state->i;
		return ;
	}
	state->i++;
}

void	ft_fill_result_helper(char **result, char *str, char c)
{
	t_result_state	state;

	ft_init_fill_result(&state);
	while (str[state.i] && str[state.i] == c)
		state.i++;
	state.start = state.i;
	while (str[state.i])
		ft_process_fill_result_char(&state, str, c, result);
	if (state.i > state.start)
		result[state.j++] = ft_substr(str, state.start, state.i - state.start);
	result[state.j] = NULL;
}
