/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:31:11 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/31 16:25:07 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(t_parser **pars, char *str, int i, int count)
{
	handle_space(pars, str, i, count);
	if (!(*pars))
		return (pars_error("|"));
	lst_push_back(pars, list_new("|", PIPE, 3, 1));
	return (i + 1);
}
int	handle_less(t_parser **pars, char *str, int i, int count)
{
	int	k;
	
	handle_space(pars, str, i, count);
	if (is_delitimer(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new(">", GREATHER, 4, 1));
	k = 0;
	while ((int)ft_strlen(str) >= i + k && str[i + ++k])
	{
		if (str[i + k] != ' ' ||
			check_tayp(token_name(str + i + k)))
			return (i);
	}
	return (pars_error("newline"));
}
int	handle_greather(t_parser **pars, char *str, int i, int count)
{
	int	k;

	handle_space(pars, str, i, count);
	if (is_delitimer(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new(">", GREATHER, 4, 1));
	k = 0;
	while ((int)ft_strlen(str) >= i + k && str[i + ++k])
	{
		if (str[i + k] != ' ' ||
			check_tayp(token_name(str + i + k)))
			return (i);
	}
	return (pars_error("newline"));
}
void	handle_space(t_parser **pars, char *str, int i, int count)
{
	if (is_space(str,count,i))
		return ;
	if (is_delitimer(*pars))
		lst_push_back(pars, list_new(ft_substr(str, count, i - count), WORD, 0, 3));
	else
		lst_push_back(pars, list_new(ft_substr(str, count, i - count), WORD, 0, 2));
}
int	handle_double_left(t_parser **pars, char *str, int i, int count)
{
	int		start;
	int		end;
	char	*limiter;
	
	handle_space(pars, str, i, count);
	if (is_delitimer(*pars))
		lst_push_back(pars, list_new("(NULL)", WORD, 0, 1));
	lst_push_back(pars, list_new("<<", DOUBLE_LEFT, 4, 1));
	start = i + 2;
	while (str[start] && str[start] == ' ')
		start++;
	end = ft_limit_end(str,i,start);
	if (!end)
		return (0);
	limiter = ft_substr(str, start, end - start);
	if (limiter)
	{
		lst_push_back(pars, list_new(limiter, WORD, 0, 1));
		free(limiter);
		return(end - 1);
	}
	return (pars_error("newline"));
}
