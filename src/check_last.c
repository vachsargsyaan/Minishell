/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:27:42 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/18 19:35:59 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static	last_hd(t_init *init, t_parser *stack)
{
	if (init->last_hdoc < 0)
		stack->last_hdoc = 1;
	init->last_hdoc = 1;
}

void static	last_redir(t_init *init, t_parser *stack)
{
	if (init->last_redir < 0)
		stack->last_red = 1;
	init->last_redir = 1;
}

void static	last_input(t_init *init, t_parser *stack)
{
	if (init->last_input < 0)
		stack->last_input = 1;
	init->last_input = 1;
}

int	ch_reds(t_init *init, t_parser *stack, int mode)
{
	if (mode == 1)
	{
		init->last_hdoc = -42;
		init->last_redir = -42;
		init->last_input = -42;
		return (1);
	}
	last_hd(init, stack);
	last_redir(init, stack);
	last_input(init, stack);
	return (1);
}
