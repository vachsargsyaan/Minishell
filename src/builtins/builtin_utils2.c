/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghumash <sghumash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:04:13 by sghumash          #+#    #+#             */
/*   Updated: 2024/02/01 16:49:32 by sghumash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*line(int len, char *p, long long n)
{
	unsigned long long	a;

	p[len] = '\0';
	len--;
	if (n < 0)
	{
		p[0] = '-';
		a = (unsigned long long)(n * -1);
		while (a != 0)
		{
			p[len--] = (a % 10) + '0';
			a /= 10;
		}
	}
	else
	{
		while (n != 0)
		{
			p[len--] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (p);
}

char	*ft_itul(long long n)
{
	char		*p;
	long long	len;

	p = NULL;
	if (n == 0)
		return (zerocase(p));
	len = digit_count(n);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	return (line(len, p, n));
}

char	*zerocase(char *m)
{
	m = (char *)malloc(sizeof(char) * 2);
	m[0] = 0 + '0';
	m[1] = 0;
	return (m);
}
