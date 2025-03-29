/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:16:37 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:16:38 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	limit;

	i = 0;
	while (dst[i] != '\0')
		i++;
	if (siz <= i)
		return (ft_strlen(src) + siz);
	else
	{
		limit = siz - 1 - i;
		j = 0;
		while (src[j] != '\0' && j < limit)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
		return (i + ft_strlen(src));
	}
}
