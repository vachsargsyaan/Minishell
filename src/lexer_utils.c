/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:23:26 by vacsargs          #+#    #+#             */
/*   Updated: 2024/02/01 16:23:20 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_error(char *str, int i)
{
	if (str[0] == '(' || str[0] == '\'' || str[0] == '"')
		ft_dprintf(STDERR_FILENO, "syntax error missing token `%s'\n", str);
	else
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `%s\n", str);
	if (i == 1)
		free(str);
	return (0);
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
	if (root->tayp == PIPE || root->tayp == HEREDOC || root->tayp == LESS_THAN)
		return (1);
	else if (root->tayp == AND || root->tayp == OR)
		return (1);
	else if (root->tayp == GREATHER || root->tayp == DOUBLE_RIGHT)
		return (1);
	else if (root->tayp == SUBSH_OPEN || root->tayp == SUBSH_CLOSE)
		return (3);
	else
		return (0);
}

int	handle_double_right(t_parser **pars, char *str, int i, int count)
{
	handle_space(pars, str, i, count);
	if (is_delimiter(*pars) && is_delimiter(*pars) != 3)
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new(">>", DOUBLE_RIGHT, 4, 1));
	return (i + 1);
}
