/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:50:18 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/30 19:06:26 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_or(t_parser **pars, char *str, int *i, int count)
{
	if (!(*pars))
		return (pars_error("||", *i + 1));
	handle_space(pars, str, *i, count);
	lst_push_back(pars, list_new("||", OR, 2, 1));
	return (*i + 1);
}

int	handle_and(t_parser **pars, char *str, int *i, int count)
{
	if (!(*pars))
		return (pars_error("&&", *i + 1));
	handle_space(pars, str, *i, count);
	lst_push_back(pars, list_new("&&", AND, 2, 1));
	return (*i + 1);
}

int	lexer2(t_parser **pars, char *str, int *i, int counter)
{
	if (str[*i] == ')')
		*i = handle_sub(pars, str, *i, counter);
	else if (str[*i] == '(')
		*i = handle_clprnth(pars, str, *i, counter);
	else if (str[*i] == '&' && str[*i + 1] == '&')
		*i = handle_and(pars, str, i, counter);
	else if (str[*i] == '|' && str[*i + 1] == '|')
		*i = handle_or(pars, str, i, counter);
	else if (str[*i] == '>' && str[*i + 1] == '>')
		*i = handle_double_right(pars, str, i, counter);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		*i = handle_heredoc(pars, str, i, counter);
	else if (str[*i] == '>')
		*i = handle_greather(pars, str, i, counter);
	else if (str[*i] == '<')
		*i = handle_less(pars, str, i, counter);
	else if (str[*i] == '|')
		*i = handle_pipe(pars, str, i, counter);
	else if (ft_strchr(" \n\t\v\r\f", str[*i]))
		handle_space(pars, str, *i, counter);
	else if (str[*i + 1] == '\0')
		handle_space(pars, str, *i + 1, counter);
	else
		return (0);
	return (1);
}

int	lexer1(t_parser **pars, char *str, int *i, int counter)
{
	int	key;

	while (str[*i])
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			key = handle_quotes(pars, str, i, counter);
			if (key)
				return (key);
		}
		else if (!lexer2(pars, str, i, counter))
		{
			(*i)++;
			continue ;
		}
		break ;
	}
	return (0);
}

int	lexer(t_parser **pars, char *str)
{
	int	i;
	int	counter ;

	i = 0;
	while (str && str[i])
	{
		counter = i;
		if (lexer1(pars, str, &i, counter) == -42)
			return (0);
		i++;
	}
	lst_push_back(pars, list_new("AST", END, 1, 2));
	return (1);
}

void	lex(t_init *init, char *str, t_env *env)
{
	(void)env;
	g_exit_status_ = 0;
	if (!lexer(&(init->lex), str) || !init->lex)
	{
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	if (heredoc_valid(init, init->lex))
		exit (2);
	parser(init);
}
