/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:24:27 by vacsargs          #+#    #+#             */
/*   Updated: 2023/11/10 20:49:53 by vacsargs         ###   ########.fr       */
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

t_parser	*lstlast(t_parser *lst)
{
	t_parser	*ptr;

	ptr = lst;
	if (!ptr)
		return (NULL);
	while (ptr && ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
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

char	*strjoin_mode(char *s1, char *s2, int mode)
{
	if (mode == 1)
		s1 = ft_strjoin(s1, "\n", 1);
	else
		s1 = ft_strjoin(s1, " ", 1);
	s1 = ft_strjoin(s1, s2, 1);
	return (s1);
}
