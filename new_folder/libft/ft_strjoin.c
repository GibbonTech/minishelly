/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:16:25 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:16:31 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int		i;
	unsigned int		j;
	char				*new;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (s1[i] != '\0')
		{
			new[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2[j] != '\0')
		{
			new[i + j] = s2[j];
			j++;
		}
		new[i + j] = '\0';
		return (new);
	}
}
