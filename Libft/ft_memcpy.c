/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:31:31 by vacsargs          #+#    #+#             */
/*   Updated: 2023/01/28 20:19:11 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*c;

	d = (char *)dst;
	c = (char *)src;
	if (!dst && !src)
		return (0);
	if ((dst == src) || n == 0)
		return (dst);
	while (n--)
	d[n] = c[n];
	return (d);
}
