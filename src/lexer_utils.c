/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:23:26 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/18 15:35:21 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_error(char *str, int i)
{
	if (str[0] == '(')
		ft_dprintf(STDERR_FILENO,"syntax error missing token `%s'\n", ")");
	else
		ft_dprintf(STDERR_FILENO,"syntax error near unexpected token `%s\n", str);
	return (i);
}

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

int	is_delimiter(t_parser *pars)
{
	t_parser	*root;

	root = pars;
	if (!root)
		return (2);
	root = lst_last_token(root);
	if (root->tayp == PIPE || root->tayp == DOUBLE_LEFT || root->tayp == INPUT)
		return (1);
	else if (root->tayp == AND || root->tayp == OR)
		return (1);
	else if (root->tayp == GREATHER || root->tayp == LESS_THAN)
		return (1);
	else
		return (0);
}

int	handle_double_right(t_parser **pars, char *str, int *i, int count)
{
	int	p;

	if (!is_space(str, count, *i) && is_delimiter(*pars))
		lst_push_back(pars, list_new(ft_substr
				(str, count, *i - count), WORD, 0, 1));
	else if (!is_space(str, count, *i))
		lst_push_back(pars, list_new(ft_substr
				(str, count, *i - count), WORD, 0, 0));
	else if (is_delimiter(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 0));
	lst_push_back(pars, list_new(">>", DOUBLE_RIGHT, 4, 1));
	p = 1;
	while ((int)ft_strlen(str) >= *i + p && str[*i + ++p])
	{
		if (str[*i + p] != ' ')
			return (*i + 1);
	}
	return (pars_error("newline", *i +1));
}
