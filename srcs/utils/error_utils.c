/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:50:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 15:50:05 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_print_numeric_error(char *cmd, char *arg, char *message, int *code)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	*code = 2;
}
