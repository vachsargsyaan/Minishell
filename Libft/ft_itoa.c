/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:57:27 by vacsargs          #+#    #+#             */
/*   Updated: 2023/02/02 19:23:06 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static long	ft_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	ft_ch(long n, int lenght)
{
	while (--lenght)
		n /= 10;
	n %= 10;
	return (n + '0');
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	int		len;
	long	n2;

	i = 0;
	n2 = n;
	len = ft_len(n2);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	if (n < 0)
	{
		p[i++] = '-';
		n2 *= -1;
		len--;
	}
	while (len)
		p[i++] = ft_ch(n2, len--);
	p[i] = '\0';
	return (p);
}
