/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:17:14 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:17:15 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char				*sub;
	unsigned int		i;

	if (ft_strlen(s) < start || len == 0)
		return (ft_strdup(s + ft_strlen(s)));
	if ((ft_strlen(s) - 1) == start || ft_strlen(s + start) < len)
		return (ft_strdup(s + start));
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
