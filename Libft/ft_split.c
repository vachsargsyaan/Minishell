/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:26:52 by vacsargs          #+#    #+#             */
/*   Updated: 2023/02/02 16:02:49 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_len(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (j);
}

static	char	**ft_erkar(char const *s, char c, char **p)
{
	size_t	i;
	size_t	j;
	size_t	m;
	size_t	z;

	j = 0;
	m = 0;
	z = 0;
	while (s[j])
	{
		i = 0;
		if (s[j] != c)
		{
			m = j;
			while (s[j] && s[j++] != c)
				i++;
			p[z] = ft_substr(s, m, i);
			z++;
		}
		else
		j++;
	}
	return (p);
}

static	void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	int		a;
	char	**p;

	if (!s)
		return (NULL);
	if (*s == '\0')
	{
		p = malloc(1 * sizeof(char *));
		p[0] = NULL;
		return (p);
	}
	a = ft_len(s, c);
	p = malloc(sizeof(char *) * a);
	if (!p)
		return (NULL);
	if (!a)
	{
		ft_free(p, a);
		return (0);
	}
	p[a - 1] = NULL;
	p = ft_erkar(s, c, p);
	return (p);
}
