/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:39:28 by vacsargs          #+#    #+#             */
/*   Updated: 2023/02/06 18:09:59 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*c;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	c = malloc(count * size);
	if (!c)
		return (NULL);
	ft_bzero (c, count * size);
	return (c);
}
