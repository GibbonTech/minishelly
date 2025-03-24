/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/23 20:10:46 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_heredoc(t_command *cmd, char *delimiter, t_minishell *minishell)
{
	char		*file;
	int			fd;
	static int	count = 0;

	file = ft_create_heredoc_file(&count);
	if (!file)
		return (-1);
	if (!ft_open_heredoc_file(file, &fd))
		return (-1);
	if (!ft_read_heredoc(fd, delimiter, minishell))
	{
		close(fd);
		unlink(file);
		free(file);
		return (-1);
	}
	close(fd);
	if (!ft_setup_heredoc_input(cmd, file))
		return (-1);
	return (0);
}
