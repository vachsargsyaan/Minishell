/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:24:27 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/15 18:02:05 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
