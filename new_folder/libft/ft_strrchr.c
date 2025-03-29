/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:17:05 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:17:06 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int			i;
	char					*result;
	unsigned char			character;

	character = (unsigned char) c;
	result = (char *)s;
	if (character == '\0')
		return (result + ft_strlen(s));
	if (result[0] == '\0' && character != '\0')
		return (NULL);
	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		if (result[i] == character)
			return (result + i);
		i--;
	}
	if (result[0] == character)
		return (result);
	return (NULL);
}
