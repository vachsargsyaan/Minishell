/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:00:07 by vacsargs          #+#    #+#             */
/*   Updated: 2023/10/02 16:40:52 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_init(t_parser *lex, t_init *init)
{
	int 		i;
	t_parser *tmp;
	
	i = 0;
	tmp = lex;
	while (1)
	{
		if (i == 0 && tmp->tayp == HEREDOC)
			lst_push_back(&(init->pars),list_new("<<", HEREDOC, tmp->prc, tmp->flag));
		else if (i == 1 && tmp->tayp == DOUBLE_RIGHT)
			lst_push_back(&(init->pars),list_new(">>", DOUBLE_RIGHT, tmp->prc, tmp->flag));
		else if (i == 1 && tmp->tayp == GREATHER)
			lst_push_back(&(init->pars),list_new(">", GREATHER, tmp->prc, tmp->flag));
		else if (i == 1 && tmp->tayp == LESS_THAN)
			lst_push_back(&(init->pars),list_new("<", LESS_THAN,tmp->prc, tmp->flag));
		else if (i == 2 && tmp->tayp == PIPE)
			lst_push_back(&(init->pars),list_new("|",  PIPE, tmp->prc, tmp->flag));
		else if (i == 3 && tmp->tayp == WORD)
			lst_push_back(&(init->pars),list_new(tmp->cmd, WORD, tmp->prc, tmp->flag));
		if (tmp->next == NULL)
		{
			i++;
			tmp = lex;
		}
		tmp = tmp->next;
		if (i == 4)
			break;
	}
	i = 0;
	while (init->pars != NULL)
	{
		printf("%s ", init->pars->cmd);
		init->pars = init->pars->next;
	}
}
void	parser(t_init *init)
{
	t_parser	*tmp;
	t_parser	*postfix;
	t_parser	*opstack;

	postfix = NULL;
	opstack = NULL;
	tmp = init->lex;
	parser_init(tmp,init);
}
