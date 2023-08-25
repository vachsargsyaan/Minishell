/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:23:26 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/20 19:22:12 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*lst_last_token(t_parser *lst)
{
	t_parser	*ptr;

	ptr = lst;
	if (!ptr)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

int	is_space(char *str, int i, int j)
{
	while (i < j && str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
int	is_delitimer(t_parser *pars)
{
	t_parser	*root;

	root = pars;
	if (!root)
		return (2);
	root = lst_last_token(root);
	if (root->tayp == PIPE || root->tayp == DOUBLE_LEFT || root->tayp == INPUT)
		return (1);
	else if (root->tayp == AND || root->tayp == VERTICAL_BAR)
		return (1);
	else if (root->tayp == 	LEFT_PARENTHESIS || root->tayp == RIGHT_PARENTHESIS)
		return (1);
	else if (root->tayp == GREATHER || root->tayp == LESS_THAN)
		return (1);
	else
		return (0);
}