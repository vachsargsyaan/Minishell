/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:00:07 by vacsargs          #+#    #+#             */
/*   Updated: 2023/11/10 20:49:24 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shunting_yard(t_parser **p, t_parser **ops, t_parser **otp)
{
	if ((*p)->prc == 0)
		lst_push_back(otp, ast_branch(*p));
	else if ((*p)->prc > 0)
	{
		if ((*p)->tayp == SUBSH_CLOSE)
		{
			while (*ops && lstlast(*ops)->tayp != SUBSH_OPEN)
				push(ops, otp);
			lstlast(*otp)->sub = 1;
			pop(ops);
		}
		else if ((*p)->tayp != SUBSH_OPEN)
		{
			while (*ops && lstlast(*ops)->prc >= (*p)->prc \
				&& lstlast(*ops)->tayp != SUBSH_OPEN)
				push(ops, otp);
			lst_push_back(ops, ast_branch(*p));
		}
		else
			lst_push_back(ops, ast_branch(*p));
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
	while (tmp)
	{
		shunting_yard(&tmp, &postfix, &opstack);
		tmp = tmp->next;
	}
	while (opstack != NULL)
	{
		printf("%s\n", opstack->cmd);
		opstack = opstack->next;
	}
}
