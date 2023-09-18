/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:10:10 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/15 17:54:09 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tayp(t_name type)
{
	if (type == OR || type == AND || type == PIPE)
		return (1);
	else if (type == GREATHER || type == DOUBLE_RIGHT)
		return (1);
	else if (type == DOUBLE_LEFT || type == LESS_THAN)
		return (1);
	return (0);
}

char	*token_is(t_name token)
{
	if (token == DQUOTE)
		return ("\"");
	else if (token == SQUOTE)
		return ("'");
	else if (token == SUBSH_OPEN)
		return ("(");
	else if (token == SUBSH_CLOSE)
		return (")");
	else if (token == OR)
		return ("||");
	else if (token == AND)
		return ("&&");
	else if (token == PIPE)
		return ("|");
	else if (token == DOUBLE_LEFT)
		return ("<<");
	else if (token == DOUBLE_RIGHT)
		return (">>");
	else if (token == GREATHER)
		return (">");
	else if (token == LESS_THAN)
		return ("<");
	else
		return ("newline");
}

t_name	token_name(char *token)
{
	if (token[0] == '"')
		return (DQUOTE);
	else if (token[0] == '\'')
		return (SQUOTE);
	else if (token[0] == '(')
		return (SUBSH_OPEN);
	else if (token[0] == ')')
		return (SUBSH_CLOSE);
	else if (token[0] == '|' && token[1] == '|')
		return (OR);
	else if (token[0] == '&' && token[1] == '&')
		return (AND);
	else if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '<' && token[1] == '<')
		return (DOUBLE_LEFT);
	else if (token[0] == '>' && token[1] == '>')
		return (DOUBLE_RIGHT);
	else if (token[0] == '>')
		return (GREATHER);
	else if (token[0] == '<')
		return (LESS_THAN);
	else if (token[0] == '\0')
		return (END);
	return (WORD);
}

int	ft_limit_end(char *str, int i, int start)
{
	int	end;

	end = start;
	while (str[end] && str[end] != ' ')
	{
		if (str[end] == '&' && str[end + 1] == '&')
			break ;
		else if (str[end] == '|' || str[end] == '<' || str[end] == '>')
			break ;
		else if (str[end] == '(' || str[end] == ')')
			break ;
		end++;
	}
	if (end == start)
	{
		if (str[i] == '\0')
			return (pars_error("newline", 0));
		else
			return (pars_error(token_is(token_name(str + start)), 0));
	}
	return (end);
}
