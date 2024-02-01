/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:31:11 by vacsargs          #+#    #+#             */
/*   Updated: 2024/02/01 16:22:56 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(t_parser **pars, char *str, int *i, int count)
{
	handle_space(pars, str, *i, count);
	if (!(*pars))
		return (pars_error("|", 0) - 42);
	lst_push_back(pars, list_new("|", PIPE, 3, 1));
	return (*i);
}

int	handle_less(t_parser **pars, char *str, int *i, int count)
{
	handle_space(pars, str, *i, count);
	if (is_delimiter(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new("<", LESS_THAN, 4, 1));
	return (*i);
}

int	handle_greather(t_parser **pars, char *str, int *i, int count)
{
	handle_space(pars, str, *i, count);
	if (is_delimiter(*pars) && is_delimiter(*pars) != 3)
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new(">", GREATHER, 4, 1));
	return (*i);
}

void	handle_space(t_parser **pars, char *str, int i, int count)
{
	char	*res;

	res = NULL;
	if (is_space(str, count, i))
		return ;
	res = ft_substr(str, count, i - count);
	if (is_delimiter(*pars))
		lst_push_back(pars, list_new(res, WORD, 0, 3));
	else if (count > 1 && str[count - 1] == ' ')
		lst_push_back(pars, list_new(res, WORD, 0, 2));
	else
		lst_push_back(pars, list_new(res, WORD, 0, 0));
	if (res)
		free(res);
}

int	handle_heredoc(t_parser **pars, char *str, int *i, int count)
{
	handle_space(pars, str, *i, count);
	if (is_delimiter(*pars) && is_delimiter(*pars) != 3)
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new("<<", HEREDOC, 4, 1));
	return (*i + 1);
}
