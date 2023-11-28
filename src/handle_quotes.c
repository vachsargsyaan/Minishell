/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:29:36 by vacsargs          #+#    #+#             */
/*   Updated: 2023/11/11 15:12:44 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count(char *line, char c)
{
	int	dquote;
	int	squote;
	int	i;

	i = -1;
	dquote = ((squote = 0));
	while (line && line[++i])
	{
		if (line[i] == '"')
			dquote++;
		if (line[i] == '\'')
			squote++;
	}
	if (c == '\'')
		return (squote);
	else if (c == '"')
		return (dquote);
	return (dquote + squote);
}

int	add_new_quote(t_parser **res, char *line, int i, int type)
{
	int		counter;
	char	c;
	char	*str;

	c = '\0';
	if (type == DQUOTE)
		c = '"';
	else if (type == SQUOTE)
		c = '\'';
	counter = i + 1;
	while (line[counter] && line[counter] != c)
		counter++;
	if (line[i] == '\'' || line[i] == '"')
		str = ft_substr(line, i + 1, counter - i - 1);
	else
		str = ft_substr(line, i, counter - i);
	if (line[counter] == c && is_delimiter(*res))
		lst_push_back(res, list_new(str, type, 0, 1));
	else if (line[counter] == c && i > 1 && line[i - 1] == ' ')
		lst_push_back(res, list_new(str, type, 0, 2));
	else if (line[counter] == c)
		lst_push_back(res, list_new(str, type, 0, 0));
	free(str);
	return (counter);
}

int	handle_dquotes(t_parser **pars, char **str, int *i, int count)
{
	int		val;

	handle_space(pars, *str, *i, count);
	val = add_new_quote(pars, *str, *i, DQUOTE);
	if (quote_count(*str, '"') % 2)
	{
		pars_error("\"", 0);
		return (*i = -10);
	}
	return (*i = val);
}

int	handle_squotes(t_parser **pars, char **str, int *i, int count)
{
	int		p;

	handle_space(pars, *str, *i, count);
	p = add_new_quote(pars, *str, *i, SQUOTE);
	if (quote_count(*str, '\'') % 2)
	{
		pars_error("'", 0);
		return (*i = -10);
	}
	return (*i = p);
}

char	*handle_quotes(t_parser **pars, char **str, int *i, int counter)
{
	int	status;

	if ((*str)[*i] == '\'')
	{
		status = handle_squotes(pars, str, i, counter);
		if (status < 0)
			return ("\'");
	}
	if ((*str)[*i] == '\"')
	{
		status = handle_dquotes(pars, str, i, counter);
		if (status < 0)
			return ("\"");
	}
	return (NULL);
}
