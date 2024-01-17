/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:17:41 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/10 15:17:05 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wcard_logic_2(char **pattern, char **string, int star)
{
	while (**string != '\0')
	{
		if (**pattern == **string)
		{
			(*pattern)++;
			(*string)++;
		}
		else if (**pattern == '*')
		{
			star = 1;
			(*pattern)++;
		}
		else if (star)
		{
			if (ft_strcmp(*string, *pattern - 1))
				while (**pattern != '*')
					(*pattern)--;
			++(*string);
			if (**pattern == '*' || \
			(**string == '\0' && **pattern && !strcmp(*string - 1, *pattern)))
				(*pattern)++;
		}
		else
			return ;
	}
}

int	wcard_logic(char *pattern, char *string)
{
	if (pattern[0] != '.' && string[0] == '.')
		return (0);
	wcard_logic_2(&pattern, &string, 0);
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}
