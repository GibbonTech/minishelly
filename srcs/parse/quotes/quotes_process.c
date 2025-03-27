/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:29:21 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 10:39:05 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper structure to group parameters
 */
typedef struct s_quote_params
{
	int		i;
	int		j;
	char	quote_state;
}	t_quote_params;

/**
 * Helper function to process a quote character
 * @param str Input string
 * @param result Pointer to store the result
 * @param params Pointer to quote processing parameters
 */
static void	ft_handle_quote_char(char *str, char **result,
		t_quote_params *params)
{
	if ((str[params->i] == '\'' || str[params->i] == '\"')
		&& !params->quote_state)
	{
		params->quote_state = str[params->i];
		(params->i)++;
	}
	else if (str[params->i] == params->quote_state)
	{
		params->quote_state = 0;
		(params->i)++;
	}
	else
		(*result)[(params->j)++] = str[(params->i)++];
}

/**
 * Process a string to remove quotes
 * @param str Input string
 * @param result Pointer to store the result
 * @return Pointer to the result or NULL on error
 */
char	*ft_process_quotes_simple(char *str, char **result)
{
	t_quote_params	params;

	if (!str)
		return (NULL);
	params.i = 0;
	params.j = 0;
	params.quote_state = 0;
	*result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!*result)
		return (NULL);
	while (str[params.i])
	{
		ft_handle_quote_char(str, result, &params);
	}
	(*result)[params.j] = '\0';
	return (*result);
}

char	*ft_remove_quotes_from_str(char *str)
{
	char	*result;

	result = NULL;
	if (!str)
		return (NULL);
	if (!ft_process_quotes_simple(str, &result))
		return (NULL);
	return (result);
}

void	ft_remove_quotes(t_token *token)
{
	char	*new_str;

	if (!token || !token->token_name)
		return ;
	new_str = ft_remove_quotes_from_str(token->token_name);
	if (new_str)
	{
		free(token->token_name);
		token->token_name = new_str;
	}
}
