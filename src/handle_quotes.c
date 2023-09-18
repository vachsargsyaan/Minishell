/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:29:36 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/15 17:53:29 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dquotes(t_parser **pars, char *str, int *i, int count)
{
	int		p;
	char	*s;

	handle_space(pars, str, *i, count);
	p = *i +1;
	while (str[p] && str[p] != '"')
		p++;
	if (str[*i] == '"')
		s = ft_substr(str, *i + 1, p - *i - 1);
	else
		s = ft_substr(str, *i, p - *i);
	if ((str[p] == '"' && is_delimiter(*pars)) || is_delimiter(*pars) == -1)
		lst_push_back(pars, list_new(s, DQUOTE, 0, 1));
	else if (str[p] == '"' && *i > 1 && str[*i - 1] == ' ')
		lst_push_back(pars, list_new(s, DQUOTE, 0, 2));
	else if (str[p] == '"')
		lst_push_back(pars, list_new(s, DQUOTE, 0, 0));
	else
	{
		free(s);
		return (pars_error("\"", 0));
	}
	free(s);
	*i = p;
	return (p);
}

int	handle_squotes(t_parser **pars, char *str, int *i, int count)
{
	int		p;
	char	*a;

	handle_space(pars, str, *i, count);
	p = *i + 1;
	while (str[p] && str[p] != '"')
		p++;
	a = ft_substr(str, *i + 1, p - *i - 1);
	if (str[p] == '\'' && is_delimiter(*pars))
		lst_push_back(pars, list_new(a, SQUOTE, 0, 1));
	else if (str[p] == '\'' && *i > 1 && str[*i - 1] == ' ')
		lst_push_back(pars, list_new(a, SQUOTE, 0, 2));
	else if (str[p] == '\'')
		lst_push_back(pars, list_new(a, SQUOTE, 0, 0));
	else
	{
		free(a);
		return(pars_error("'", 0));
	}
	free(a);
	return (p);
}
int	handle_quotes(t_parser **pars, char *str, int *i, int counter)
{
	int	status;

	if (str[*i] == '\'')
	{
		status = handle_squotes(pars,str,i,counter);
		if (status < 0)
			return (status);
	}
	if (str[*i] == '\"')
	{
		status = handle_dquotes(pars,str,i,counter);
		if (status < 0)
			return (status);
	}
	return (0);
}