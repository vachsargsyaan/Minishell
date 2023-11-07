/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:00:00 by vacsargs          #+#    #+#             */
/*   Updated: 2023/01/25 20:56:44 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	char const	*p;

	p = s1;
	if (!p || !set)
		return (0);
	while (*p && ft_strchr(set, *p))
		++p;
	if (*p == '\0')
		return (ft_strdup(""));
	i = ft_strlen(p);
	--i;
	while (i && ft_strchr(set, p[i]))
		--i;
	return (ft_substr(p, 0, i + 1));
}
