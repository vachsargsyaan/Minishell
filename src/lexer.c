/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:50:18 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/26 16:34:37 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_vertical_bar(t_parser **pars, char *str, int i, int count)
{
	if (!(*pars))
		printf("syntax error near unexpected token `||'\n");
	if (!is_space(str, count, i) && is_delitimer(*pars))
		lst_push_back(pars, list_new(ft_substr(str, count, i - count), WORD, 0, 1));
	else if (!is_space(str, count, i))
		lst_push_back(pars, list_new(ft_substr(str, count, i - count), WORD, 0, 0));
	lst_push_back(pars, list_new("||", OR, 2, 1));
	return(i +2);
}

void	handle_space(t_parser **pars, char *str, int i, int count)
{
	char *tmp;

	tmp = str;
	if (is_space(str, count, i))
		return ;
	tmp = ft_substr(tmp,count, i - count);
	if (is_delitimer(*pars))
		lst_push_back(pars, list_new(tmp, WORD, 0, 3));
	else if (count > 1 && str[count - 1] == ' ')
		lst_push_back(pars, list_new(tmp, WORD, 0, 2));
	else
		lst_push_back(pars, list_new(tmp, WORD, 0, 0));
	if (tmp)
		free(tmp);
}
int	handle_and(t_parser **pars, char *str, int i, int count)
{
	if (!(*pars))
		printf("syntax error near unexpected token `&&'\n");
	if (!is_space(str, count, i) && is_delitimer(*pars))
		lst_push_back(pars, list_new(ft_substr(str, count, i - count), WORD, 0, 1));
	else if (!is_space(str, count, i))
		lst_push_back(pars, list_new(ft_substr(str, count, i - count), WORD, 0, 0));
	lst_push_back(pars, list_new("&&", AND, 2, 1));
	return(i +2);
}
void	lexer(t_parser **pars, char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i] && str)
	{
		count = i;
		while (str[i] != '\0')
		{
			if (str[i] == '&' && str[i + 1] == '&')
				handle_and(pars, str, i, count);
			else if (str[i] == '|' && str[i + 1] == '|')
				handle_vertical_bar(pars, str, i, count);
			else if (str[i] == '>' && str[i + 1] == '>')
				handle_double_right(pars, str, i, count);
			// else if (str[i] == '<' && str[i + 1] == '<')
			// 	handle_double_left(pars, str, i, count);
			else if (str[i] =='(')
				handle_space(pars, str, i, count);
			else if (str[i] == '>')
				handle_space(pars, str, i, count);
			else if (str[i] == '<')
				handle_space(pars, str, i, count);
			else if (str[i] == '|')
				handle_space(pars, str, i, count);
			else if(ft_strchr("\n\t", str[i]))
				handle_space(pars, str, i, count);
			else if (str[i + 1] == '\0')
				handle_space(pars, str, i + 1, count);
			else
			{
				handle_space(pars, str, i + 1, count);
				i++;
				continue ;
			}
			break ;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
}
void	lex(t_init *init, char *str)
{
	lexer(&(init->lex), str);
}