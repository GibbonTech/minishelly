/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_preprocessing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/26 11:16:07 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_operator_spaces(char *input, int i)
{
	int	count;

	count = 0;
	if ((i > 0 && input[i - 1] != ' ') && (i > 0 && input[i - 1] != '<'
			&& input[i - 1] != '>'))
		count++;
	if (input[i + 1] && input[i + 1] != ' ' && ((input[i] == '>' && input[i
					+ 1] == '>') || (input[i] == '<' && input[i + 1] == '<')))
	{
		i++;
		if (input[i + 1] && input[i + 1] != ' ')
			count++;
	}
	else if (input[i + 1] && input[i + 1] != ' ' && input[i + 1] != '>'
		&& input[i + 1] != '<')
		count++;
	return (count);
}

static void	ft_handle_quote_count(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i])
		(*i)++;
}

static int	ft_count_spaces_needed(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			ft_handle_quote_count(input, &i);
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			count += ft_count_operator_spaces(input, i);
			if (input[i + 1] && ((input[i] == '>' && input[i + 1] == '>')
					|| (input[i] == '<' && input[i + 1] == '<')))
				i++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static void	ft_process_quote(char *input, char *result, int *i, int *j)
{
	char	quote;

	quote = input[*i];
	result[(*j)++] = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		result[(*j)++] = input[(*i)++];
	if (input[*i])
		result[(*j)++] = input[(*i)++];
}

char	*ft_insert_spaces_around_operators(char *input)
{
	char	*result;
	int		spaces_needed;
	int		i;
	int		j;

	if (!input)
		return (NULL);
	spaces_needed = ft_count_spaces_needed(input);
	result = malloc(ft_strlen(input) + spaces_needed * 2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			ft_process_quote(input, result, &i, &j);
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			ft_handle_operator(input, result, &i, &j);
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
