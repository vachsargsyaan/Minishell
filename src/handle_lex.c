/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:31:11 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/15 18:02:51 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(t_parser **pars, char *str, int *i, int count)
{
	handle_space(pars, str, *i, count);
	if (!(*pars))
		return (pars_error("|", *i));
	lst_push_back(pars, list_new("|", PIPE, 3, 1));
	return (*i);
}

int	handle_less(t_parser **pars, char *str, int *i, int count)
{
	int	k;

	handle_space(pars, str, *i, count);
	if (is_delimiter(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new("<", LESS_THAN, 4, 1));
	k = 0;
	while ((int)ft_strlen(str) >= *i + k && str[*i + ++k])
	{
		if (str[*i + k] != ' '
			|| check_tayp(token_name(str + *i + k)))
			return (*i);
	}
	return (pars_error("newline", 0));
}

int	handle_greather(t_parser **pars, char *str, int *i, int count)
{
	int	k;

	handle_space(pars, str, *i, count);
	if (is_delimiter(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new(">", GREATHER, 4, 1));
	k = 0;
	while ((int)ft_strlen(str) >= *i + k && str[*i + ++k])
	{
		if (str[*i + k] != ' '
			|| check_tayp(token_name(str + *i + k)))
			return (*i);
	}
	return (pars_error("newline", 0));
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

int	handle_double_left(t_parser **pars, char *str, int *i, int count)
{
	handle_space(pars, str, *i, count);
	if (is_delimiter(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new("<<", DOUBLE_LEFT, 4, 1));
	return(*i+1);
}
