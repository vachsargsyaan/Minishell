/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:39:46 by vacsargs          #+#    #+#             */
/*   Updated: 2023/02/01 17:07:35 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	c;

	p = (char *)hay;
	i = 0;
	j = ft_strlen(need);
	if (hay == NULL && len == 0)
		return (NULL);
	if (j == 0 || hay == need)
		return (p);
	while (p[i] != '\0' && i < len)
	{
		c = 0;
		while (p[i + c] != '\0' && need != '\0'\
				&& p[i + c] == need[c] && i + c < len)
			c++;
		if (c == j)
			return (p + i);
		i++;
	}
	return (0);
}
