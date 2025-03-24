/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:35:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 01:26:12 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *minishell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	(void)minishell;
}
