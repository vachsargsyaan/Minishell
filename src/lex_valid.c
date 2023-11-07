/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:45:31 by vacsargs          #+#    #+#             */
/*   Updated: 2023/11/01 17:06:21 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	subshell_validation(t_parser *tmp, int *sb)
{
	if (tmp->tayp == SUBSH_OPEN)
		(*sb)++;
	else if (tmp->tayp == SUBSH_CLOSE)
		(*sb)--;
	if (tmp->tayp == SUBSH_CLOSE && (!tmp->prev || tmp->next->tayp == SUBSH_OPEN || (*sb) < 0))
		return (pars_error(")", 0 + (*sb == 0)));
	if (tmp->tayp == SUBSH_CLOSE && (tmp->next->tayp == WORD || tmp->next->tayp == SQUOTE || tmp->next->tayp == DQUOTE))
		return (pars_error(tmp->next->cmd, 0 + (*sb == 0)));
	if (tmp->tayp == SUBSH_CLOSE && tmp->prev && !check_tayp(tmp->prev->tayp))
	{
		if (tmp->next->tayp != END && tmp->prev->tayp != SUBSH_OPEN)
			return (pars_error (tmp->next->cmd, 0) + (*sb == 0));
		else if (tmp->prev->tayp != SUBSH_CLOSE)
			return (pars_error("newline", 0) + (*sb == 0));
	}
	return (1);
}

int	check_valid(t_init *init, t_env *env, int *sb, int fl)
{
	t_parser	*tmp;

	(void)env;
	(void)fl;
	tmp = init->lex;
	while (tmp->next != NULL)
	{
		if (!subshell_validation(tmp, sb))
			return (0);
		if (check_tayp(tmp->tayp) == 2 && !ft_strcmp(tmp->next->cmd, "*"))
			return(dprintf(2, "Minishell: *: ambiguous redirect\n"), 0);
		if (check_tayp(tmp->tayp) && check_tayp(tmp->next->tayp) == 1)
			return (pars_error(type_is(tmp->next->tayp), 0));
		if (check_tayp(tmp->tayp) == 1 && tmp->prev == NULL)
			return (pars_error(type_is(tmp->tayp), 0));
		if (check_tayp(tmp->tayp) == 2 && !ft_strcmp(tmp->next->cmd, "(NULL)"))
			if (tmp->next->next)
				return (pars_error(type_is(tmp->next->next->tayp), 0));
		if (check_tayp(tmp->tayp) && tmp->next->tayp == END)
			return (pars_error("newline", 0));
		if (tmp->tayp == HEREDOC && ft_strcmp(tmp->next->cmd, "(NULL)") && !fl)
			read_heredoc_input(init, tmp, NULL, env);
		if ((check_tayp(tmp->tayp) == 2 && tmp->tayp != HEREDOC) && !fl)
			find_limiter(init, tmp->next);
		tmp = tmp->next;
	}
	return (1);
}
