/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:39:46 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/19 19:57:33 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr( char *str, char *str1, int len)
{
	int		i;

	i = 0;
	if (len == 0)
	{
		while (str[i] == str1[i])
			i++;
		if (str[i] || str1[i])
			return (str);
		else
			return (NULL);
	}
	else
	{
		while (str[i] == str1[i] && i < len)
			i++;
		if (str[i] != '\0' || str1[i] != '\0')
			return (str);
		else
			return (NULL);
	}
}
