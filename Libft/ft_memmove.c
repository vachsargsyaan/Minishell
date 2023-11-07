/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:31:21 by vacsargs          #+#    #+#             */
/*   Updated: 2023/02/07 17:05:57 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void	*dst, const void	*src, size_t	len)
{
	unsigned char	*srt;
	unsigned char	*vip;

	if (!dst && !src)
		return (NULL);
	if ((dst == 0 && src == 0) || len == 0)
		return (dst);
	srt = (unsigned char *) dst;
	vip = (unsigned char *) src;
	if (dst == src)
		return (dst);
	if (srt < vip)
		while (len--)
			*srt++ = *vip++;
	else
		while (len--)
			srt[len] = vip[len];
	return (dst);
}
