/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing_utils6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:46:04 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/28 18:46:04 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_delimiter(char *str, int *i, char c, bool *in_word)
{
	if (*in_word)
		*in_word = false;
	while (str[*i] && str[*i] == c)
		(*i)++;
}

static int	ft_count_parts_init(t_word_state *state, int *i)
{
	state->count = 0;
	state->in_quotes = false;
	state->in_word = false;
	*i = 0;
	return (0);
}

int	ft_count_parts_helper(char *str, char c)
{
	t_word_state	state;
	int				i;

	ft_count_parts_init(&state, &i);
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (ft_update_word_state(str, i, &state.in_quotes, &state.in_word))
		{
			i++;
			continue ;
		}
		if (str[i] == c && !state.in_quotes)
		{
			state.count += state.in_word;
			ft_process_delimiter(str, &i, c, &state.in_word);
			continue ;
		}
		state.in_word = true;
		i++;
	}
	return (state.count + state.in_word);
}
