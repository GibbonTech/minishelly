/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:49:47 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 07:41:24 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* External functions from:
 * cmd_processing_utils2.c, cmd_processing_utils3.c and cmd_processing_utils4.c
 */
int			ft_word_len(char *str);
size_t		ft_count_words(const char *s, char c);
void		ft_skip_spaces(char *str, int *i);
void		ft_allocate_word(char **args, char *cmd_cell, int i, int j);
char		**ft_split_with_quotes(char *str, char c);

char	**ft_split_cmd_args(char *cmd_cell)
{
	char	**args;
	int		word_count;
	int		i;
	int		j;

	if (!cmd_cell)
		return (NULL);
	word_count = ft_count_words(cmd_cell, ' ');
	args = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	ft_skip_spaces(cmd_cell, &i);
	while (j < word_count)
	{
		ft_allocate_word(args, cmd_cell, i, j);
		if (!args[j])
			return (NULL);
		i += ft_word_len(&cmd_cell[i]);
		ft_skip_spaces(cmd_cell, &i);
		j++;
	}
	args[word_count] = NULL;
	return (args);
}

bool	ft_cmd_struct(char *input, t_minishell *minishell)
{
	char	**cmd_cells;
	int		i;

	cmd_cells = ft_split_with_quotes(input, '|');
	if (!cmd_cells)
		return (false);
	i = 0;
	while (cmd_cells[i])
		i++;
	if (!ft_create_cmd_list(minishell, cmd_cells))
	{
		ft_free_table(cmd_cells);
		return (false);
	}
	ft_free_table(cmd_cells);
	return (true);
}
