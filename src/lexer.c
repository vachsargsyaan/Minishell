/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:50:18 by vacsargs          #+#    #+#             */
/*   Updated: 2023/12/06 17:16:43 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_and(t_parser **pars, char *str, int *i, int count)
{
	handle_space(pars, str, *i, count);
	if (!(*pars))
		return (pars_error("&&", 0) - 42);
	lst_push_back(pars, list_new("&&", AND, 2, 1));
	return (*i + 1);
}

int	lexer2(t_parser **pars, char **str, int *i, int counter)
{
	if ((*str)[*i] == ')')
		*i = handle_sub(pars, *str, *i, counter);
	else if ((*str)[*i] == '(')
		*i = handle_clprnth(pars, *str, *i, counter);
	else if ((*str)[*i] == '&' && (*str)[*i + 1] == '&')
		*i = handle_and(pars, *str, i, counter);
	else if ((*str)[*i] == '|' && (*str)[*i + 1] == '|')
		*i = handle_or(pars, *str, i, counter);
	else if ((*str)[*i] == '>' && (*str)[*i + 1] == '>')
		*i = handle_double_right(pars, *str, *i, counter);
	else if ((*str)[*i] == '<' && (*str)[*i + 1] == '<')
		*i = handle_heredoc(pars, *str, i, counter);
	else if ((*str)[*i] == '>')
		*i = handle_greather(pars,*str, i, counter);
	else if ((*str)[*i] == '<')
		*i = handle_less(pars, *str, i, counter);
	else if ((*str)[*i] == '|')
		*i = handle_pipe(pars, *str, i, counter);
	else if (ft_strchr(" \n\t\v\r\f", (*str)[*i]))
		handle_space(pars, *str, *i, counter);
	else if ((*str)[*i + 1] == '\0')
		handle_space(pars, *str, *i + 1, counter);
	else
		return (0);
	return (1);
}

int	lexer1(t_parser **pars, char **str, int *i, int counter)
{
	while ((*str)[*i])
	{
		if ((*str)[*i] == '"' || (*str)[*i] == '\'')
			handle_quotes(pars, str, i, counter);
		else if (!lexer2(pars, str, i, counter))
		{
			(*i)++;
			continue ;
		}
		if (*i < 0)
			return (1);
		break ;
	}
	return (0);
}

int	lexer(t_parser **pars, char **str)
{
	int	i;
	int	counter ;

	i = 0;
	while (*str && (*str)[i])
	{
		counter = i;
		if (lexer1(pars, str, &i, counter))
		{
			return (0);
		}
		i++;
	}
	lst_push_back(pars, list_new("AST", END, 1, 2));
	return (1);
}

void	lex(t_init *init, char **str, t_env *env)
{
	int	sb;

	sb = 0;
	g_exit_status_ = 0;
	if (!lexer(&(init->lex), str) ||!check_valid(init, env, &sb, 0) || \
		!check_valid(init, env, &sb, 1) || sb > 0 || !init->lex)
	{
		if (sb > 0)
			dprintf(2, "minishell: syntax error: missing token `)'\n");
		init->exit_status = 258;
		return ;
	}
	if (heredoc_valid(init, init->lex))
		exit (2);
	parser(init);
}
