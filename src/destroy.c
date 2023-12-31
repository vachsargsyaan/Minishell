/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:48:58 by vacsargs          #+#    #+#             */
/*   Updated: 2023/11/10 20:51:18 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_init(t_init *init)
{
	t_parser	*tmp;
	t_parser	*stack;

	stack = init->lex;
	while (stack != NULL)
	{
		tmp = stack->next;
		free(stack->cmd);
		free(stack);
		stack = tmp;
	}
}
