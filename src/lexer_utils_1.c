/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:24:27 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/22 18:47:55 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*type_is(t_name type)
{
	if (type == PIPE)
		return ("|");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == LESS_THAN)
		return ("<");
	else if (type == DOUBLE_RIGHT)
		return (">>");
	else if (type == GREATHER)
		return (">");
	else if (type == END)
		return ("END");
	return ("");
}

t_parser	*lstlast(t_parser *pars)
{
	t_parser	*tmp;

	tmp = pars;
	if (tmp)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	handle_sub(t_parser **pars, char *str, int i, int count)
{
	handle_space(pars, str, i, count);
	lst_push_back(pars, list_new(")", SUBSH_CLOSE, 1, 0));
	return (i);
}

int	handle_clprnth(t_parser **pars, char *str, int i, int count)
{
	handle_space(pars, str, i, count);
	lst_push_back(pars, list_new("(", SUBSH_OPEN, 1, 0));
	return (i);
}

int	check_valid(t_init *init)
{
	t_parser	*tmp;

	tmp = init->lex;
	while (tmp->next != NULL)
	{
		if (check_tayp(tmp->tayp) && check_tayp(tmp->next->tayp) == 1)
			return (pars_error(type_is(tmp->next->tayp), 0));
		if (check_tayp(tmp->tayp) == 1 && tmp->prev == NULL)
			return (pars_error(type_is(tmp->tayp), 0));
		if (check_tayp(tmp->tayp) == 2 && !ft_strcmp(tmp->next->cmd, "(NULL)"))
			if (tmp->next->next)
				return (pars_error(type_is(tmp->next->next->tayp), 0));
		if (check_tayp(tmp->tayp) && tmp->next->tayp == END)
			return (pars_error("newline", 0));
		tmp = tmp->next;
	}
	return (1);
}
